#include "easy_lua.hpp"

easy_lua* easy_lua::initialize(
    const std::string& include_directory )
{    
    const auto l = luaL_newstate();
    if( !l ) {
        return nullptr;
    }

    luaL_openlibs( l );
    if( !include_directory.empty() ) {
        script_directory.assign( include_directory );
    }

    if( !script_directory.empty() ) {
        reinterpret_cast<easy_lua*>( l )->export_function( "include", []( easy_lua* lua ) -> int32_t 
        {
            if( lua->is_string( 1 ) ) {
                auto query = script_directory;
                if( query.back() != '\\' && query.back() != '/' ) {
                    query.append( "\\" );
                }
                query.append( lua->get_string( 1 ) );

                if( lua->load_file( query ) != State_Success && lua->pcall( 0, 0, 0 ) != State_Success ) {
                    printf( "Failed to include file: %s\n", lua->get_string( -1 ) );
                }
            }
            return 0;
        } );
    }

    return reinterpret_cast<easy_lua*>( l );
}

easy_lua* easy_lua::shared(
    void* obj )
{
    static void* shared_obj = nullptr;
    if( !shared_obj && obj != nullptr ) {
        shared_obj = obj;
    }
    return reinterpret_cast<easy_lua*>( shared_obj );
}

void easy_lua::close(
    easy_lua** lua )
{
    if( lua && *lua ) {
        ( *lua )->close();
        *lua = nullptr;
    }
}

bool easy_lua::execute(
    const std::string_view& script,
    const bool              from_memory ) const
{
    if( script.empty() ) {
        return false;
    }
    if( !from_memory ) {
        return !luaL_dofile( EASY_LUA_CAST_LUA( this ), script.data() );
    }
    if( luaL_loadstring( EASY_LUA_CAST_LUA( this ), script.data() ) > 0 ) {
        return false;
    }
    if( lua_pcall( EASY_LUA_CAST_LUA( this ), 0, 0, 0 ) > 0 ) {
        if( pop( 1 ) == this ) {
            return false;
        }
        return false;
    }
    return true;
}

bool easy_lua::is_bool(
    const int32_t stackpos ) const
{
    return lua_isboolean( EASY_LUA_CAST_LUA( this ), stackpos );
}

bool easy_lua::is_number(
    const int32_t stackpos ) const
{
    return lua_isnumber( EASY_LUA_CAST_LUA( this ), stackpos ) == 1;
}

bool easy_lua::is_string(
    const int32_t stackpos ) const
{
    return lua_isstring( EASY_LUA_CAST_LUA( this ), stackpos ) == 1;
}

bool easy_lua::is_userdata(
    const int32_t stackpos ) const
{
    return lua_isuserdata( EASY_LUA_CAST_LUA( this ), stackpos ) == 1;
}

bool easy_lua::is_nil(
    const int32_t stackpos ) const
{
    return lua_isnil( EASY_LUA_CAST_LUA( this ), stackpos );
}

bool easy_lua::get_bool(
    const int32_t stackpos,
    const bool    default_value,
    const bool    pop_value ) const
{ 
    if( is_number( stackpos ) ) {
        return get_number(
            stackpos,
            static_cast<lua_Number>( 0 ),
            pop_value
        ) >= 1.0;
    }
    if( !lua_isboolean( EASY_LUA_CAST_LUA( this ), stackpos ) ) {
        return default_value;
    }
        
    const auto v = lua_toboolean( EASY_LUA_CAST_LUA( this ), stackpos ) == 1;
    if( pop_value ) {
        if( pop( 1 ) == this ) {
            return v;
        }
    }

    return v;
}

const char* easy_lua::get_string(
    const int32_t stackpos,
    const bool    pop_value ) const
{
    const auto buffer = lua_tostring( EASY_LUA_CAST_LUA( this ), stackpos );
    if( pop_value ) {
        if( pop( 1 ) == this ) {
            return buffer;
        }
    }
    return buffer;
}

easy_lua::EState easy_lua::load_file(
    const std::string_view& file ) const
{
    switch( luaL_loadfile( EASY_LUA_CAST_LUA( this ), file.data() ) ) {
    case LUA_ERRSYNTAX:
        return State_Syntax;
    case LUA_ERRMEM:
        return State_MemAlloc;
    default:
        break;
    }
    return State_Success;
}

easy_lua::EState easy_lua::pcall(
    const int32_t num_args,
    const int32_t num_results,
    const int32_t error_function ) const
{
    switch( lua_pcall( EASY_LUA_CAST_LUA( this ), num_args, num_results, error_function ) ) {
    case LUA_ERRRUN:
        return State_Runtime;
    case LUA_ERRSYNTAX:
        return State_Syntax;
    case LUA_ERRMEM:
        return State_MemAlloc;
    case LUA_ERRERR:
        return State_ErrHandling;
    default:
        break;
    }
    return State_Success;
}

bool easy_lua::top(
    const size_t needed ) const
{
    return static_cast<size_t>( top() ) == needed;
}

bool easy_lua::top(
    const size_t mins,
    const size_t maxs ) const
{
    const auto is = static_cast<size_t>( top() );
    return is >= mins && is <= maxs;
}

const easy_lua* easy_lua::export_class(
    const std::string_view& global_name,
    const std::string_view& metatable_name,
    std::vector<LuaCFunc>   functions ) const
{
    if( global_name.empty() || metatable_name.empty() || functions.empty() ) {
        return nullptr;
    }

    if( functions.back().name != nullptr && functions.back().callback != nullptr ) {
        functions.push_back( { nullptr, nullptr } );
    }

    luaL_newmetatable( EASY_LUA_CAST_LUA( this ), metatable_name.data() );

    /// For lua 5.2 and above: luaL_setfuncs( l, funcs, nullptr );
    luaL_register( EASY_LUA_CAST_LUA( this ), nullptr, reinterpret_cast<const luaL_Reg*>( functions.data() ) );
    lua_pushvalue( EASY_LUA_CAST_LUA( this ), -1 );
    lua_setfield( EASY_LUA_CAST_LUA( this ), -1, "__index" );
    lua_setglobal( EASY_LUA_CAST_LUA( this ), global_name.data() );

    return this;
}

const easy_lua* easy_lua::export_class(
    const MetaTableArray& metatable_data,
    std::vector<LuaCFunc> functions ) const
{
    return export_class( metatable_data[ 0 ], metatable_data[ 1 ], std::move( functions ) );
}

const easy_lua* easy_lua::export_function(
    const std::string_view& name,
    const FnCallback        callback ) const
{
    if( name.empty() || !callback ) {
        return nullptr;
    }
    lua_register( 
        EASY_LUA_CAST_LUA( this ), 
        name.data(), 
        reinterpret_cast<lua_CFunction>( callback )
    );

    return this;
}

const easy_lua* easy_lua::get_global(
    const std::string_view& name ) const
{
    lua_getglobal( EASY_LUA_CAST_LUA( this ), name.data() );
    return this;
}

const easy_lua* easy_lua::set_global(
    const std::string_view& name ) const
{
    if( name.empty() ) {
        return nullptr;
    }

    lua_setglobal( EASY_LUA_CAST_LUA( this ), name.data() );

    return this;
}

const easy_lua* easy_lua::pop(
    const int32_t num_elements ) const
{
    lua_pop( EASY_LUA_CAST_LUA( this ), num_elements );
    return this;
}

const easy_lua* easy_lua::pop_top() const
{
    lua_pop( EASY_LUA_CAST_LUA( this ), top() );
    return this;
}

const easy_lua* easy_lua::push_bool(
    const bool value ) const
{
    lua_pushboolean( EASY_LUA_CAST_LUA( this ), value ? 1 : 0 );
    return this;
}

const easy_lua* easy_lua::push_string(
    const std::string_view& str ) const
{
    lua_pushstring( EASY_LUA_CAST_LUA( this ), str.data() );
    return this;
}

const easy_lua* easy_lua::push_nil() const
{
    lua_pushnil( EASY_LUA_CAST_LUA( this ) );
    return this;
}

int32_t easy_lua::destroy_userdata(
    const int32_t      stackpos,
    const std::string_view& name ) const
{
    if( is_userdata( stackpos ) && !name.empty() ) {
        const auto data = get_userdata<uintptr_t>( stackpos, name );
        delete data;
    }
    return 0;
}

int32_t easy_lua::top() const
{
    return lua_gettop( EASY_LUA_CAST_LUA( this ) );
}

int32_t easy_lua::pushed(
    const int32_t val ) const
{
    if( !EASY_LUA_CAST_LUA( this ) ) {
        return 0;
    }
    return val;
}

void easy_lua::close()
{
    lua_close( EASY_LUA_CAST_LUA( this ) );
}

std::string easy_lua::script_directory;
