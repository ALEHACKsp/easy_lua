///-------------------------------------------------------------------------------------------------
/// Author:             ReactiioN
/// Created:            18.02.2017
/// 
/// Last modified by:   ReactiioN
/// Last modified on:   18.01.2018
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
/// # Timestamp: 18.01.2018
/// # https://github.com/ReactiioN1337/easy_lua
/// # supported lua version: LuaJIT 2.0.5
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
#pragma once
#include <lua.hpp>
#include <array>
#include <string>
#include <string_view>
#include <vector>

#if !defined(_HAS_CXX17)
#error "easy_lua requires a compiler which supports C++17"
#endif

#if !defined(EASY_LUA_CAST_LUA)
#define EASY_LUA_CAST_LUA(ptr)  (lua_State*)ptr
#endif

#if !defined(EASY_LUA_CAST_EASY)
#define EASY_LUA_CAST_EASY(ptr) (easy_lua*)ptr
#endif

#if !defined(EASY_LUA_CREATE_METATABLE_DATA)
#define EASY_LUA_CREATE_METATABLE_DATA(name, global) static easy_lua::MetaTableArray name = { \
    global,                                                                                   \
    #name                                                                                     \
    }
#endif

#if !defined(EASY_LUA_MAKE_PLUGIN)
#define EASY_LUA_MAKE_PLUGIN(onPluginLoad, onPluginUnload, onPluginGetDescription) extern "C" {   \
    bool __declspec(dllexport) plugin_load( easy_lua* lua )                                       \
    {                                                                                             \
        return onPluginLoad( lua );                                                               \
    }                                                                                             \
    void __declspec(dllexport) plugin_unload()                                                    \
    {                                                                                             \
        onPluginUnload();                                                                         \
    }                                                                                             \
    void __declspec(dllexport) plugin_get_description( easy_lua::PluginDescription* description ) \
    {                                                                                             \
        onPluginGetDescription( description );                                                    \
    }                                                                                             \
}
#endif

class easy_lua
{
public:
    using MetaTableArray = std::array<std::string_view, 2>;

    enum EState : uint8_t
    {
        /// <summary> 
        /// An enum constant representing the state success option. 
        /// </summary>
        State_Success = 0,
        /// <summary> 
        /// An enum constant representing the state runtime option. 
        /// </summary>
        State_Runtime,
        /// <summary> 
        /// An enum constant representing the state syntax option. 
        /// </summary>
        State_Syntax,
        /// <summary> 
        /// An enum constant representing the state Memory Allocate option. 
        /// </summary>
        State_MemAlloc,
        /// <summary> 
        /// An enum constant representing the state Error handling option. 
        /// </summary>
        State_ErrHandling,
    };

    struct PluginDescription
    {
        /// <summary> 
        /// The author.
        /// </summary>
        std::string author;
        /// <summary> 
        /// The version. 
        /// </summary>
        std::string version;
        /// <summary> 
        /// The description.
        /// </summary>
        std::string description;
    };

    /// <summary> 
    /// The load plugin callback typedef.
    /// </summary>
    using FnLoadPlugin   = bool( *)( easy_lua* );

    /// <summary> 
    /// The unload plugin callback typedef.
    /// </summary>
    using FnUnloadPlugin = void( *)();

private:
    /// <summary> 
    /// The callback function typedef. 
    /// </summary>
    using FnCallback = int32_t( *)( easy_lua* );

    typedef struct LuaCFunc
    {
        /// <summary>
        /// The function name. </summary>
        const char* name;

        /// <summary> 
        /// The callback function.
        /// </summary>
        FnCallback  callback;
    }LuaCFunc;

    /// <summary> 
    /// The supported version number. 
    /// </summary>
    constexpr static double supported_version_number = 503;
    /// <summary> 
    /// The major version. 
    /// </summary>
    constexpr static auto   major_version            = 5;
    /// <summary> 
    /// The minor version. 
    /// </summary>
    constexpr static auto   minor_version            = 3;
    /// <summary> 
    /// The release version. 
    /// </summary>
    constexpr static auto   release_version          = 3;

protected:
    easy_lua() = default;

public:
    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Initializes this object. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="include_directory">    Pathname of the include directory. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to an easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    static easy_lua* initialize(
        const std::string& include_directory );

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Shared the given object. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="obj">  [in,out] (Optional) If non-null, the object. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to an easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    static easy_lua* shared(
        void* obj = nullptr );

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Closes the given lua. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="lua">  [in,out] If non-null, the lua. </param>
    ///-------------------------------------------------------------------------------------------------
    static void close(
        easy_lua** lua );

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Executes. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="script">       The script. </param>
    /// <param name="from_memory">  (Optional) True to from memory. </param>
    ///
    /// <returns>   True if it succeeds, false if it fails. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool execute(
        const std::string_view& script,
        bool                    from_memory = false ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Query if 'stackpos' is bool. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   True if bool, false if not. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool is_bool(
        int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Query if 'stackpos' is number. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   True if number, false if not. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool is_number(
        int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Query if 'stackpos' is string. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   True if string, false if not. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool is_string(
        int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Query if 'stackpos' is userdata. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   True if userdata, false if not. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool is_userdata(
        int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Query if 'stackpos' is nil. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   True if nil, false if not. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool is_nil(
        int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets a bool. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="stackpos">         The stackpos. </param>
    /// <param name="default_value">    (Optional) True to default value. </param>
    /// <param name="pop_value">        (Optional) True to pop value. </param>
    ///
    /// <returns>   True if it succeeds, false if it fails. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool get_bool(
        int32_t stackpos,
        bool    default_value = false,
        bool    pop_value = false ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets a string. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="stackpos">         The stackpos. </param>
    /// <param name="pop_value">        (Optional) True to pop value. </param>
    ///
    /// <returns>   Null if it fails, else the string. </returns>
    ///-------------------------------------------------------------------------------------------------
    const char* get_string(
        int32_t stackpos,
        bool    pop_value = false ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Loads a file. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="file"> The file. </param>
    ///
    /// <returns>   The file. </returns>
    ///-------------------------------------------------------------------------------------------------
    EState load_file(
        const std::string_view& file ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pcalls. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="num_args">         Number of arguments. </param>
    /// <param name="num_results">      Number of results. </param>
    /// <param name="error_function">   The error function. </param>
    ///
    /// <returns>   An EState. </returns>
    ///-------------------------------------------------------------------------------------------------
    EState pcall(
        int32_t num_args,
        int32_t num_results,
        int32_t error_function ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Tops the given needed. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="needed">   The needed. </param>
    ///
    /// <returns>   True if it succeeds, false if it fails. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool top(
        size_t needed ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Tops. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="mins"> The mins. </param>
    /// <param name="maxs"> The maxs. </param>
    ///
    /// <returns>   True if it succeeds, false if it fails. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool top(
        size_t mins,
        size_t maxs ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Export class. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="global_name">      Name of the global. </param>
    /// <param name="metatable_name">   Name of the metatable. </param>
    /// <param name="functions">        The functions. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* export_class(
        const std::string_view&    global_name,
        const std::string_view&    metatable_name,
        std::vector<LuaCFunc> functions ) const;

    const easy_lua* export_class(
        const MetaTableArray& metatable_data,
        std::vector<LuaCFunc> functions ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Export a C function. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="name">     The name. </param>
    /// <param name="callback"> The callback. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* export_function(
        const std::string_view& name,
        FnCallback         callback ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets a global. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="name"> The name. </param>
    ///
    /// <returns>   Null if it fails, else the global. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* get_global(
        const std::string_view& name ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Sets a global. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="name"> The name. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* set_global(
        const std::string_view& name ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Removes 'num_elements' from the top-of-stack and returns this object. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="num_elements"> The Number elements to pop. </param>
    ///
    /// <returns>   Null if it fails, else this object. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* pop(
        int32_t num_elements ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Removes the top-of-stack and returns this object. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <returns>   Null if it fails, else this object. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* pop_top() const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes a bool. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="value">    True to value. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* push_bool(
        bool value ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes a string. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="str">  The string. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* push_string(
        const std::string_view& str ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes the nil. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* push_nil() const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Destroys the userdata. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    /// <param name="name">     The name. </param>
    ///
    /// <returns>   An int32_t. </returns>
    ///-------------------------------------------------------------------------------------------------
    int32_t destroy_userdata(
        int32_t                 stackpos,
        const std::string_view& name ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushed the given value. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <param name="val">  The value. </param>
    ///
    /// <returns>   An int32_t. </returns>
    ///-------------------------------------------------------------------------------------------------
    int32_t pushed(
        int32_t val ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets the top. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <returns>   An int32_t. </returns>
    ///-------------------------------------------------------------------------------------------------
    int32_t top() const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Closes this object. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///-------------------------------------------------------------------------------------------------
    void close();

public:
    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Creates a new userdata. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    ///
    /// <returns>   Null if it fails, else a handle to a T. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    T** new_userdata() const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes a number. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="value">    The value. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    const easy_lua* push_number(
        T value ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes an integer. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="value">    The value. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    const easy_lua* push_integer(
        T value ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes an userdata. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="name"> The name. </param>
    /// <param name="data"> [in,out] If non-null, the data. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    const easy_lua* push_userdata(
        const std::string_view& name,
        T*                      data ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets a number. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="stackpos">         The stackpos. </param>
    /// <param name="default_value">    (Optional) The default value. </param>
    /// <param name="pop_value">        (Optional) True to pop value. </param>
    ///
    /// <returns>   The number. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T = lua_Number>
    T get_number(
        int32_t stackpos,
        T       default_value = static_cast<T>( 0 ),
        bool    pop_value = false ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets an integer. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="stackpos">         The stackpos. </param>
    /// <param name="default_value">    (Optional) The default value. </param>
    /// <param name="pop_value">        (Optional) True to pop value. </param>
    ///
    /// <returns>   The integer. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T = lua_Integer>
    T get_integer(
        int32_t stackpos,
        T       default_value = static_cast<T>( 0 ),
        bool    pop_value = false ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets an userdata. </summary>
    ///
    /// <remarks>   ReactiioN, 18.01.2018. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="stackpos">     The stackpos. </param>
    /// <param name="name">         The name. </param>
    /// <param name="pop_value">    (Optional) True to pop value. </param>
    ///
    /// <returns>   Null if it fails, else the userdata. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    T* get_userdata(
        int32_t                 stackpos,
        const std::string_view& name,
        bool                    pop_value = false ) const;

    template<typename T>
    T* get_userdata(
        int32_t               stackpos,
        const MetaTableArray& metatable_data,
        bool                  pop_value = false ) const;

public:
    static std::string script_directory;
};

template<typename T>
T** easy_lua::new_userdata() const
{
    return reinterpret_cast<T**>(
        lua_newuserdata( EASY_LUA_CAST_LUA( this ), sizeof( T* ) )
    );
}

template<typename T>
const easy_lua* easy_lua::push_number(
    const T value ) const
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    lua_pushnumber( EASY_LUA_CAST_LUA( this ), static_cast<lua_Number>( value ) );
    return this;
}

template<typename T>
const easy_lua* easy_lua::push_integer(
    const T value ) const
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    lua_pushinteger( EASY_LUA_CAST_LUA( this ), static_cast<lua_Integer>( value ) );
    return this;
}

template<typename T>
const easy_lua* easy_lua::push_userdata(
    const std::string_view& name,
    T*                 data ) const
{
    if( !name.empty() && data ) {
        auto created_data = new_userdata<T>();
        if( created_data ) {
            *created_data = data;
            luaL_getmetatable( EASY_LUA_CAST_LUA( this ), name.data() );
            lua_setmetatable( EASY_LUA_CAST_LUA( this ), -2 );
            return this;
        }
    }
    return nullptr;
}

template<typename T>
T easy_lua::get_number(
    const int32_t stackpos,
    const T       default_value,
    const bool    pop_value ) const
{
    if( is_number( stackpos ) ) {
        auto n = static_cast<T>( lua_tonumber( EASY_LUA_CAST_LUA( this ), stackpos ) );
        if( pop_value ) {
            if( pop( 1 ) == this ) {
                return n;
            }
        }
        return n;
    }
    return default_value;
}

template<typename T>
T easy_lua::get_integer(
    const int32_t stackpos,
    const T       default_value,
    const bool    pop_value ) const
{
    if( is_number( stackpos ) ) {
        auto i = static_cast<T>( lua_tointeger( EASY_LUA_CAST_LUA( this ), stackpos ) );
        if( pop_value ) {
            if( pop( 1 ) == this ) {
                return i;
            }
        }
        return i;
    }
    return default_value;
}

template<typename T>
T* easy_lua::get_userdata(
    const int32_t           stackpos,
    const std::string_view& name,
    const bool              pop_value ) const
{
    if( is_userdata( stackpos ) && !name.empty() ) {
        const auto v = luaL_checkudata(
            EASY_LUA_CAST_LUA( this ),
            stackpos,
            name.data()
        );
        if( v ) {
            if( pop_value ) {
                if( pop( 1 ) == this ) {
                    return *reinterpret_cast<T**>( v );
                }
            }
            return *reinterpret_cast<T**>( v );
        }
    }
    return nullptr;
}

template<typename T>
T* easy_lua::get_userdata(
    const int32_t         stackpos,
    const MetaTableArray& metatable_data,
    const bool            pop_value ) const
{
    return get_userdata<T>( stackpos, metatable_data.at( 1 ), pop_value );
}
