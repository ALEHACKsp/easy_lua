///-------------------------------------------------------------------------------------------------
/// Author:             ReactiioN
/// Created:            18.02.2017
/// 
/// Last modified by:   ReactiioN
/// Last modified on:   07.04.2017
///-------------------------------------------------------------------------------------------------
///     Copyright (c) ReactiioN <https://reactiion.pw>. All rights reserved.
///-------------------------------------------------------------------------------------------------
///                              __
///    ___  ____ ________  __   / /_  ______ _
///   / _ \/ __ `/ ___/ / / /  / / / / / __ `/
///  /  __/ /_/ (__  ) /_/ /  / / /_/ / /_/ /
///  \___/\__,_/____/\__, /  /_/\__,_/\__,_/
///                 /____/
/// 
/// easy_lua wrapper for modern C++
/// # Author: ReactiioN
/// # Timestamp: 02.18.2017
/// # https://github.com/ReactiioN1337/easy_lua
/// # supported lua version: 5.3.3
///-------------------------------------------------------------------------------------------------
/// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
/// Copyright (c) 2016-2017 ReactiioN <https://reactiion.pw>.
///
/// Permission is hereby  granted, free of charge, to any  person obtaining a copy
/// of this software and associated  documentation files (the "Software"), to deal
/// in the Software  without restriction, including without  limitation the rights
/// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
/// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
/// furnished to do so, subject to the following conditions:
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
/// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
/// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
/// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
/// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///-------------------------------------------------------------------------------------------------
#ifndef REACTIION_EASY_LUA_HPP
#define REACTIION_EASY_LUA_HPP

#include <lua.hpp>
#include <string>

namespace lua {
/// Pathname of the lua script directory.
extern std::string lua_script_directory;

///-------------------------------------------------------------------------------------------------
/// Query if 'l' is bool.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          stack The stack.
///
/// @return True if bool, false if not.
///-------------------------------------------------------------------------------------------------
inline bool is_bool( lua_State* l, const int32_t stack )
{
    return l ? lua_isboolean( l, stack ) : false;
}

///-------------------------------------------------------------------------------------------------
/// Query if 'l' is number.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          stack The stack.
///
/// @return True if number, false if not.
///-------------------------------------------------------------------------------------------------
inline bool is_number( lua_State* l, const int32_t stack )
{
    return l ? lua_isnumber( l, stack ) > 0 : false;
}

///-------------------------------------------------------------------------------------------------
/// Query if 'l' is integer.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          stack The stack.
///
/// @return True if integer, false if not.
///-------------------------------------------------------------------------------------------------
inline bool is_integer( lua_State* l, const int32_t stack )
{
    return l ? lua_isinteger( l, stack ) > 0 : false;
}

///-------------------------------------------------------------------------------------------------
/// Query if 'l' is string.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          stack The stack.
///
/// @return True if string, false if not.
///-------------------------------------------------------------------------------------------------
inline bool is_string( lua_State* l, const int32_t stack )
{
    return l ? lua_isstring( l, stack ) > 0 : false;
}

///-------------------------------------------------------------------------------------------------
/// Query if 'l' is nil.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          stack The stack.
///
/// @return True if nil, false if not.
///-------------------------------------------------------------------------------------------------
inline bool is_nil( lua_State* l, const int32_t stack )
{
    return l ? lua_isnil( l, stack ) : false;
}

///-------------------------------------------------------------------------------------------------
/// Query if 'l' is user data.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          stack The stack.
///
/// @return True if user data, false if not.
///-------------------------------------------------------------------------------------------------
inline bool is_user_data( lua_State* l, const int32_t stack )
{
    return l ? lua_isuserdata( l, stack ) > 0 : false;
}

///-------------------------------------------------------------------------------------------------
/// Pushes a nil.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam N Type of the n.
/// @param [in,out] l If non-null, the lua_State to process.
///
/// @return An int32_t.
///-------------------------------------------------------------------------------------------------
template<int32_t N = 1>
static int32_t push_nil( lua_State* l )
{
    if( !l ) {
        return 0;
    }
    lua_pushnil( l );
    return N;
}

///-------------------------------------------------------------------------------------------------
/// Pushes a bool.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam N Type of the n.
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          value The value.
///
/// @return An int32_t.
///-------------------------------------------------------------------------------------------------
template<int32_t N = 1>
static int32_t push_bool( lua_State* l, const bool value )
{
    if( !l ) {
        return 0;
    }
    lua_pushboolean( l, value ? 1 : 0 );
    return N;
}

///-------------------------------------------------------------------------------------------------
/// Pushes a number.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam N Type of the n.
/// @tparam T Generic type parameter.
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          value The value.
///
/// @return An int32_t.
///-------------------------------------------------------------------------------------------------
template<int32_t N = 1, typename T = float>
static int32_t push_number( lua_State* l, const T value )
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    if( !l ) {
        return 0;
    }
    lua_pushnumber( l, static_cast<lua_Number>( value ) );
    return N;
}

///-------------------------------------------------------------------------------------------------
/// Pushes an int.
///
/// @author ReactiioN
/// @date 03.01.2017
///
/// @tparam N Type of the n.
/// @tparam T Generic type parameter.
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          value The value.
///
/// @return An int32_t.
///-------------------------------------------------------------------------------------------------
template<int32_t N = 1, typename T = int32_t>
static int32_t push_int( lua_State* l, const T value )
{
    static_assert( std::is_integral<T>::value, "Type T has to be integral" );
    if( !l ) {
        return 0;
    }
    lua_pushinteger( l, static_cast<lua_Integer>( value ) );
    return N;
}

///-------------------------------------------------------------------------------------------------
/// Pushes a string.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam N Type of the n.
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          value The value.
///
/// @return An int32_t.
///-------------------------------------------------------------------------------------------------
template<int32_t N = 1>
static int32_t push_string( lua_State* l, const std::string& value )
{
    if( !l ) {
        return 0;
    }
    lua_pushstring( l, value.c_str() );
    return N;
}

///-------------------------------------------------------------------------------------------------
/// Gets an int.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam T Generic type parameter.
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          stack The stack.
///
/// @return The int.
///-------------------------------------------------------------------------------------------------
template<typename T = int32_t>
static T get_int( lua_State* l, const int32_t stack, const T default_value = static_cast<T>( 0 ) )
{
    static_assert( std::is_integral<T>::value, "Type T has to be integral" );
    return l && is_integer( l, stack )
        ? static_cast<T>( lua_tointeger( l, stack ) )
        : default_value;
}

///-------------------------------------------------------------------------------------------------
/// Gets a float.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam T Generic type parameter.
/// @param [in,out] l             If non-null, the lua_State to process.
/// @param          stack         The stack.
/// @param          default_value (Optional) The default value.
///
/// @return The float.
///-------------------------------------------------------------------------------------------------
template<typename T = float>
static T get_float( lua_State* l, const int32_t stack, const T default_value = static_cast<T>( 0 ) )
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    return l && ( is_integer( l, stack ) || is_number( l, stack ) )
        ? static_cast<T>( lua_tonumber( l, stack ) )
        : default_value;
}

///-------------------------------------------------------------------------------------------------
/// Gets a bool.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l             If non-null, the lua_State to process.
/// @param          stack         The stack.
/// @param          default_value The default value.
///
/// @return True if it succeeds, false if it fails.
///-------------------------------------------------------------------------------------------------
inline bool get_bool( lua_State* l, const int32_t stack, const bool default_value = false )
{
    if( !l ) {
        return default_value;
    }
    if( is_bool( l, stack ) ) {
        return lua_toboolean( l, stack ) == 1;
    }
    if( is_number( l, stack ) || is_integer( l, stack ) ) {
        return static_cast<int32_t>( lua_tonumber( l, stack ) ) == 1;
    }
    return default_value;
}

///-------------------------------------------------------------------------------------------------
/// Gets a string.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l     If non-null, the lua_State to process.
/// @param          stack The stack.
///
/// @return Null if it fails, else the string.
///-------------------------------------------------------------------------------------------------
inline const char* get_string( lua_State* l, const int32_t stack )
{
    return l ? lua_tostring( l, stack ) : "";
}

///-------------------------------------------------------------------------------------------------
/// Executes.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l           If non-null, the lua_State to process.
/// @param          data        The data.
/// @param          from_memory from memory.
///
/// @return True if it succeeds, false if it fails.
///-------------------------------------------------------------------------------------------------
inline bool execute( lua_State* l, const std::string& data, const bool from_memory )
{
    if( !l || data.empty() ) {
        return false;
    }
    if( !from_memory ) {
        return !luaL_dofile( l, data.c_str() );
    }
    if( luaL_loadstring( l, data.c_str() ) > 0 ) {
        return false;
    }
    if( lua_pcall( l, 0, 0, 0 ) > 0 ) {
        lua_pop( l, 1 );
        return false;
    }
    return true;
}

///-------------------------------------------------------------------------------------------------
/// Tops the given l.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l If non-null, the lua_State to process.
///
/// @return An int32_t.
///-------------------------------------------------------------------------------------------------
inline int32_t top( lua_State* l )
{
    return l ? lua_gettop( l ) : -1;
}

///-------------------------------------------------------------------------------------------------
/// Check top.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam T Generic type parameter.
/// @param [in,out] l         If non-null, the lua_State to process.
/// @param          get_check The get check.
///
/// @return True if it succeeds, false if it fails.
///-------------------------------------------------------------------------------------------------
template<typename T>
static bool check_top( lua_State* l, const T get_check )
{
    static_assert( std::is_integral<T>::value, "Type T has to be integral" );
    return top( l ) == static_cast<int32_t>( get_check );
}

///-------------------------------------------------------------------------------------------------
/// Check top.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam T Generic type parameter.
/// @param [in,out] l    If non-null, the lua_State to process.
/// @param          mins The mins.
/// @param          maxs The maxs.
///
/// @return True if it succeeds, false if it fails.
///-------------------------------------------------------------------------------------------------
template<typename T>
static bool check_top( lua_State* l, const T mins, const T maxs )
{
    static_assert( std::is_integral<T>::value, "Type T has to be integral" );
    const auto t = top( l );
    return t >= static_cast<int32_t>( mins ) && t <= static_cast<int32_t>( maxs );
}

///-------------------------------------------------------------------------------------------------
/// Export class.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param [in,out] l                   If non-null, the lua_State to process.
/// @param          global_name         Name of the global.
/// @param          metatable_name      Name of the metatable.
/// @param          functions_to_export The functions to export.
///-------------------------------------------------------------------------------------------------
inline void export_class( lua_State* l, const std::string& global_name, const std::string& metatable_name, const luaL_Reg* functions_to_export )
{
    if( !l || global_name.empty() || metatable_name.empty() || !functions_to_export ) {
        return;
    }

    luaL_newmetatable( l, metatable_name.c_str() );
    luaL_setfuncs( l, functions_to_export, 0 );
    lua_pushvalue( l, -1 );
    lua_setfield( l, -1, "__index" );
    lua_setglobal( l, global_name.c_str() );
}

///-------------------------------------------------------------------------------------------------
/// Export function.
///
/// @author ReactiioN
/// @date   22.12.2016
///
/// @param [in,out] l               If non-null, the lua_State to process.
/// @param          function_name   Name of the function.
/// @param          fn              The function.
///-------------------------------------------------------------------------------------------------

inline void export_function( lua_State* l, const std::string& function_name, lua_CFunction fn )
{
    if( !l || function_name.empty() || !fn ) {
        return;
    }
    lua_register( l, function_name.c_str(), fn );
}

///-------------------------------------------------------------------------------------------------
/// Closes the given l.
///
/// @author ReactiioN
/// @date 03.01.2017
///
/// @param [in,out] l If non-null, the lua_State to process.
///-------------------------------------------------------------------------------------------------
inline void close( lua_State** l )
{
    if( !l || !*l ) {
        return;
    }
    lua_close( *l );
    *l = nullptr;
}

///-------------------------------------------------------------------------------------------------
/// Opens the given open libs.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @param open_libs (Optional) The open libs.
///
/// @return Null if it fails, else a pointer to a lua_State.
///-------------------------------------------------------------------------------------------------
inline lua_State* open( const bool open_libs = true )
{
    auto* l = luaL_newstate();
    if( open_libs ) {
        luaL_openlibs( l );
    }

    export_function( l, "include", []( lua_State* L ) -> int32_t {
        auto get_current_directory = []( const std::string& appended_file ) -> std::string
        {
            auto path = lua_script_directory;
            if( path.back() != '\\' ) {
                path.append( "\\" );
            }
            if( !appended_file.empty() ) {
                path.append( appended_file );
            }
            return path;
        };

        const auto* c = luaL_checkstring( L, 1 );
        if( c == nullptr
            || luaL_loadfile( L, get_current_directory( c ).c_str() )
            || lua_pcall( L, 0, 0, 0 ) ) {
            printf( "Error executing lua: %s", get_string( L, -1 ) );
        }
        return 0;
    } );
    return l;
}

///-------------------------------------------------------------------------------------------------
/// Creates a new userdata.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam T Generic type parameter.
/// @param [in,out] l If non-null, the lua_State to process.
///
/// @return Null if it fails, else a handle to a T.
///-------------------------------------------------------------------------------------------------
template<typename T>
static T** new_userdata( lua_State* l )
{
    return l ? reinterpret_cast<T**>( lua_newuserdata( l, sizeof( T* ) ) ) : nullptr;
}

///-------------------------------------------------------------------------------------------------
/// Pushes an userdata.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam N Type of the n.
/// @tparam T Generic type parameter.
/// @param [in,out] l             If non-null, the lua_State to process.
/// @param          userdata_name Name of the userdata.
/// @param          userdata      The userdata.
///
/// @return An int32_t.
///-------------------------------------------------------------------------------------------------
template<typename T, int32_t N = 1>
static int32_t push_userdata( lua_State* l, const std::string& userdata_name, const T* userdata )
{
    if( !l || userdata_name.empty() || !userdata ) {
        return 0;
    }

    auto** push_data = new_userdata<T>( l );
    if( !push_data ) {
        return 0;
    }
    *push_data = const_cast<T*>( userdata );

    luaL_getmetatable( l, userdata_name.c_str() );
    lua_setmetatable( l, -2 );

    return N;
}

///-------------------------------------------------------------------------------------------------
/// Gets user data.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam T Generic type parameter.
/// @param [in,out] l              If non-null, the lua_State to process.
/// @param          stack          The stack.
/// @param          metatable_name Name of the metatable.
///
/// @return Null if it fails, else the user data.
///-------------------------------------------------------------------------------------------------
template<typename T>
static T* get_user_data( lua_State* l, const int32_t stack, const std::string& metatable_name )
{
    if( !l || metatable_name.empty() || !is_user_data( l, stack ) ) {
        return nullptr;
    }
    return *reinterpret_cast<T**>( luaL_checkudata( l, stack, metatable_name.c_str() ) );
}

///-------------------------------------------------------------------------------------------------
/// Deletes the user data.
///
/// @author ReactiioN
/// @date 22.12.2016
///
/// @tparam T Generic type parameter.
/// @param [in,out] l              If non-null, the lua_State to process.
/// @param          stack          The stack.
/// @param          metatable_name Name of the metatable.
///
/// @return An int32_t.
///-------------------------------------------------------------------------------------------------
template<typename T>
int32_t delete_user_data( lua_State* l, const int32_t stack, const std::string& metatable_name )
{
    if( !is_user_data( l, stack ) || metatable_name.empty() ) {
        return 0;
    }

    auto* userdata = get_user_data<T>( l, stack, metatable_name );
    if( userdata ) {
        delete userdata;
        userdata = nullptr;
    }
    return 0;
}

///-------------------------------------------------------------------------------------------------
/// Sets a global.
///
/// @author ReactiioN
/// @date 18.02.2017
///
/// @param [in,out] l           If non-null, the lua_State to process.
/// @param          global_name Name of the global.
///-------------------------------------------------------------------------------------------------
inline void set_global( lua_State* l, const std::string& global_name )
{
    if( !global_name.empty() ) {
        lua_setglobal( l, global_name.c_str() );
    }
}

///-------------------------------------------------------------------------------------------------
/// Sets global bool.
///
/// @author ReactiioN
/// @date 18.02.2017
///
/// @param [in,out] l           If non-null, the lua_State to process.
/// @param          global_name Name of the global.
/// @param          value       The value.
///-------------------------------------------------------------------------------------------------
inline void set_global_bool( lua_State* l, const std::string& global_name, const bool value )
{
    push_bool( l, value );
    set_global( l, global_name );
}

///-------------------------------------------------------------------------------------------------
/// Sets global string.
///
/// @author ReactiioN
/// @date 18.02.2017
///
/// @param [in,out] l           If non-null, the lua_State to process.
/// @param          global_name Name of the global.
/// @param          value       The value.
///-------------------------------------------------------------------------------------------------
inline void set_global_string( lua_State* l, const std::string& global_name, const std::string& value )
{
    push_string( l, value );
    set_global( l, global_name );
}

///-------------------------------------------------------------------------------------------------
/// Sets global number.
///
/// @author ReactiioN
/// @date 18.02.2017
///
/// @tparam T Generic type parameter.
/// @param [in,out] l           If non-null, the lua_State to process.
/// @param          global_name Name of the global.
/// @param          value       The value.
///-------------------------------------------------------------------------------------------------
template<typename T>
static void set_global_number( lua_State* l, const std::string& global_name, const T value )
{
    push_number( l, value );
    set_global( l, global_name );
}

///-------------------------------------------------------------------------------------------------
/// Sets global integer.
///
/// @author ReactiioN
/// @date 18.02.2017
///
/// @tparam T Generic type parameter.
/// @param [in,out] l           If non-null, the lua_State to process.
/// @param          global_name Name of the global.
/// @param          value       The value.
///-------------------------------------------------------------------------------------------------

template<typename T>
static void set_global_integer( lua_State* l, const std::string& global_name, const T value )
{
    push_int( l, value );
    set_global( l, global_name );
}
}

#endif
