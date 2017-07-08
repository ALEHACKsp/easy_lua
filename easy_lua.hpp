///-------------------------------------------------------------------------------------------------
/// Author:             ReactiioN
/// Created:            18.02.2017
/// 
/// Last modified by:   ReactiioN
/// Last modified on:   06.07.2017
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
#pragma once
#ifndef REACTIION_EASY_LUA_HPP
#define REACTIION_EASY_LUA_HPP
/// <reference>
/// https://www.lua.org/manual/5.3/
/// </reference>
#include <lua.hpp>
/// <reference>
/// http://en.cppreference.com/w/cpp/header/string
/// </reference>
#include <string>

namespace lua {

/// <summary> 
/// The supported version number. 
/// </summary>
constexpr double supported_version_number = 503;
/// <summary> 
/// The major version. 
/// </summary>
constexpr char*  major_version            = "5";
/// <summary> 
/// The minor version. 
/// </summary>
constexpr char*  minor_version            = "3";
/// <summary> 
/// The release version. 
/// </summary>
constexpr char*  release_version          = "3";

///-------------------------------------------------------------------------------------------------
/// <summary> Query if 'l' is number. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">        [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos"> The stackpos. </param>
///
/// <returns> True if number, false if not. </returns>
///-------------------------------------------------------------------------------------------------
inline bool is_number(
    lua_State*    l,
    const int32_t stackpos )
{
    return l == nullptr
        ? nullptr
        : lua_isnumber( l, stackpos ) == 1;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Query if 'l' is integer. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">        [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos"> The stackpos. </param>
///
/// <returns> True if integer, false if not. </returns>
///-------------------------------------------------------------------------------------------------
inline bool is_integer(
    lua_State*    l,
    const int32_t stackpos )
{
    return l == nullptr
        ? nullptr
        : lua_isinteger( l, stackpos ) == 1;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Query if 'l' is bool. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">        [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos"> The stackpos. </param>
///
/// <returns> True if bool, false if not. </returns>
///-------------------------------------------------------------------------------------------------
inline bool is_bool(
    lua_State*    l,
    const int32_t stackpos )
{
    return l == nullptr
        ? nullptr
        : lua_isboolean( l, stackpos );
}

///-------------------------------------------------------------------------------------------------
/// <summary> Query if 'l' is string. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">        [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos"> The stackpos. </param>
///
/// <returns> True if string, false if not. </returns>
///-------------------------------------------------------------------------------------------------
inline bool is_string(
    lua_State*    l,
    const int32_t stackpos )
{
    return l == nullptr
        ? nullptr
        : lua_isstring( l, stackpos ) == 1;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Query if 'l' is userdata. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">        [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos"> The stackpos. </param>
///
/// <returns> True if userdata, false if not. </returns>
///-------------------------------------------------------------------------------------------------
inline bool is_userdata(
    lua_State*    l,
    const int32_t stackpos )
{
    return l == nullptr
        ? nullptr
        : lua_isuserdata( l, stackpos ) == 1;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Query if 'l' is nil. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">        [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos"> The stackpos. </param>
///
/// <returns> True if nil, false if not. </returns>
///-------------------------------------------------------------------------------------------------
inline bool is_nil(
    lua_State*    l,
    const int32_t stackpos )
{
    return l == nullptr
        ? false
        : lua_isnil( l, stackpos );
}

///-------------------------------------------------------------------------------------------------
/// <summary> Gets a number. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">             [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos">      The stackpos. </param>
/// <param name="default_value"> The default value. </param>
/// <param name="pop_value">     (Optional) True to pop value. </param>
///
/// <returns> The number. </returns>
///-------------------------------------------------------------------------------------------------
template<typename T=lua_Number>
T get_number(
    lua_State*    l,
    const int32_t stackpos,
    const T       default_value,
    const bool    pop_value = false )
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    if( is_number( l, stackpos ) ) {
        const auto v = lua_tonumber(
            const_cast<lua_State*>( l ),
            stackpos
        );
        if( pop_value ) {
            lua_pop( l, 1 );
        }
        return static_cast<T>( v );
    }
    return default_value;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Gets an integer. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">             [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos">      The stackpos. </param>
/// <param name="default_value"> The default value. </param>
/// <param name="pop_value">     (Optional) True to pop value. </param>
///
/// <returns> The integer. </returns>
///-------------------------------------------------------------------------------------------------
template<typename T=lua_Integer>
T get_integer(
    lua_State*    l,
    const int32_t stackpos,
    const T       default_value,
    const bool    pop_value = false )
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    if( is_integer( l, stackpos ) ) {
        const auto v = lua_tonumber(
            const_cast<lua_State*>( l ),
            stackpos
        );
        if( pop_value ) {
            lua_pop( l, 1 );
        }
        return static_cast<T>( v );
    }
    return default_value;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Gets a string. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">         [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos">  The stackpos. </param>
/// <param name="pop_value"> (Optional) True to pop value. </param>
///
/// <returns> Null if it fails, else the string. </returns>
///-------------------------------------------------------------------------------------------------
inline const char* get_string(
    lua_State*    l,
    const int32_t stackpos,
    const bool    pop_value = false )
{
    if( is_string( l, stackpos ) ) {
        const auto v = lua_tostring( l, stackpos );
        if( pop_value ) {
            lua_pop( l, 1 );
        }
        return v;
    }
    return "";
}

///-------------------------------------------------------------------------------------------------
/// <summary> Gets a bool. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">             [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos">      The stackpos. </param>
/// <param name="default_value"> True to default value. </param>
/// <param name="pop_value">     (Optional) True to pop value. </param>
///
/// <returns> True if it succeeds, false if it fails. </returns>
///-------------------------------------------------------------------------------------------------
inline bool get_bool(
    lua_State*    l,
    const int32_t stackpos,
    const bool    default_value,
    const bool    pop_value = false )
{
    if( !l ) {
        return default_value;
    }
    if( is_number( l, stackpos ) ) {
        return get_number(
            l,
            stackpos,
            static_cast<lua_Number>( 0 ),
            pop_value
        ) >= 1;
    }
    if( is_integer( l, stackpos ) ) {
        return get_integer(
            l,
            stackpos,
            static_cast<lua_Integer>( 0 ),
            pop_value
        ) >= 1;
    }
        
    const auto v = lua_toboolean( l, stackpos ) == 1;
    if( pop_value ) {
        lua_pop( l, 1 );
    }

    return v;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Gets an userdata. </summary>
///
/// <remarks> ReactiioN, 08.07.2017. </remarks>
///
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">              [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos">       The stackpos. </param>
/// <param name="metatable_name"> Name of the metatable. </param>
/// <param name="pop_value">      (Optional) True to pop value. </param>
///
/// <returns> Null if it fails, else the userdata. </returns>
///-------------------------------------------------------------------------------------------------
template<typename T>
T* get_userdata(
    lua_State* l,
    const int32_t      stackpos,
    const std::string& metatable_name,
    const bool         pop_value = false )
{
    if( !metatable_name.empty() && is_userdata( l, stackpos ) ) {
        auto v = luaL_checkudata( 
            l, 
            stackpos, 
            metatable_name.data() 
        );
        if( v ) {
            if( pop_value ) {
                lua_pop( l, 1 );
            }
            return *reinterpret_cast<T**>( v );
        }
    }
    return nullptr;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Pushes a bool. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="N"> Type of the n. </typeparam>
/// <param name="l">     [in,out] If non-null, a lua_State to process. </param>
/// <param name="value"> True to value. </param>
///
/// <returns> An int32_t. </returns>
///-------------------------------------------------------------------------------------------------
template<int32_t N=1>
int32_t push_bool(
    lua_State* l,
    const bool value )
{
    if( l ) {
        lua_pushboolean( l, value ? 1 : 0 );
    }
    return l != nullptr
        ? N
        : 0;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Pushes a number. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="N"> Type of the n. </typeparam>
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">     [in,out] If non-null, a lua_State to process. </param>
/// <param name="value"> The value. </param>
///
/// <returns> An int32_t. </returns>
///-------------------------------------------------------------------------------------------------
template<int32_t N = 1, typename T>
int32_t push_number(
    lua_State* l,
    const T    value )
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    if( l ) {
        lua_pushnumber( l, static_cast<lua_Number>( value ) );
    }
    return l != nullptr
        ? N
        : 0;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Pushes an integer. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="N"> Type of the n. </typeparam>
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">     [in,out] If non-null, a lua_State to process. </param>
/// <param name="value"> The value. </param>
///
/// <returns> An int32_t. </returns>
///-------------------------------------------------------------------------------------------------
template<int32_t N = 1, typename T>
int32_t push_integer(
    lua_State* l,
    const T    value )
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    if( l ) {
        lua_pushinteger( l, static_cast<lua_Integer>( value ) );
    }
    return l != nullptr
        ? N
        : 0;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Pushes a string. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="N"> Type of the n. </typeparam>
/// <param name="l">     [in,out] If non-null, a lua_State to process. </param>
/// <param name="value"> The value. </param>
///
/// <returns> An int32_t. </returns>
///-------------------------------------------------------------------------------------------------
template<int32_t N = 1>
int32_t push_string(
    lua_State*         l,
    const std::string& value )
{
    if( l ) {
        lua_pushstring( l, value.data() );
    }
    return l != nullptr
        ? N
        : 0;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Creates an userdata. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l"> [in,out] If non-null, a lua_State to process. </param>
///
/// <returns> Null if it fails, else the new userdata. </returns>
///-------------------------------------------------------------------------------------------------
template<typename T>
T** create_userdata( lua_State* l )
{
    return l == nullptr
        ? nullptr
        : reinterpret_cast<T**>(
            lua_newuserdata( l, sizeof( T* ) )
        );
}

///-------------------------------------------------------------------------------------------------
/// <summary> Destroys the userdata. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">        [in,out] If non-null, a lua_State to process. </param>
/// <param name="stackpos"> The stackpos. </param>
/// <param name="name">     The name. </param>
///
/// <returns> An int32_t. </returns>
///-------------------------------------------------------------------------------------------------
template<typename T>
int32_t destroy_userdata(
    lua_State*         l,
    const int32_t      stackpos,
    const std::string& name )
{
    if( is_userdata( l, stackpos ) && !name.empty() ) {
        auto userdata = get_userdata<T>( l, stackpos );
        if( userdata ) {
            delete userdata;
            userdata = nullptr;
        }
    }
    return 0;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Pushes an userdata. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="N"> Type of the n. </typeparam>
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">        [in,out] If non-null, a lua_State to process. </param>
/// <param name="name">     The name. </param>
/// <param name="userdata"> [in,out] If non-null, the userdata. </param>
///
/// <returns> An int32_t. </returns>
///-------------------------------------------------------------------------------------------------
template<int32_t N = 1, typename T>
int32_t push_userdata(
    lua_State*         l,
    const std::string& name,
    T*                 userdata )
{
    if( l && !name.empty() && userdata ) {
        auto created_data = create_userdata<T>( l );
        if( created_data ) {
            *created_data = userdata;
            luaL_getmetatable( l, name.c_str() );
            lua_setmetatable( l, -2 );
            return N;
        }
    }
    return 0;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Pushes a nil. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="N"> Type of the n. </typeparam>
/// <param name="l"> [in,out] If non-null, a lua_State to process. </param>
///
/// <returns> An int32_t. </returns>
///-------------------------------------------------------------------------------------------------
template<int32_t N = 1>
int32_t push_nil( lua_State* l )
{
    if( l ) {
        lua_pushnil( l );
    }
    return l != nullptr
        ? N
        : 0;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Gets a global. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">    [in,out] If non-null, a lua_State to process. </param>
/// <param name="name"> The name. </param>
///
/// <returns> True if it succeeds, false if it fails. </returns>
///-------------------------------------------------------------------------------------------------
inline bool get_global(
    lua_State*         l,
    const std::string& name )
{
    if( l && !name.empty() ) {
        lua_getglobal( l, name.data() );
        return true;
    }
    return false;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Sets a global. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">    [in,out] If non-null, a lua_State to process. </param>
/// <param name="name"> The name. </param>
///
/// <returns> True if it succeeds, false if it fails. </returns>
///-------------------------------------------------------------------------------------------------
inline bool set_global(
    lua_State*         l,
    const std::string& name )
{
    if( l && !name.empty() ) {
        lua_setglobal( l, name.data() );
        return true;
    }
    return false;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Export function. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">    [in,out] If non-null, a lua_State to process. </param>
/// <param name="name"> The name. </param>
/// <param name="fn">   The function. </param>
///-------------------------------------------------------------------------------------------------
inline void export_function(
    lua_State*         l,
    const std::string& name,
    lua_CFunction      fn )
{
    if( l && !name.empty() && fn ) {
        lua_register( l, name.data(), fn );
    }
}

///-------------------------------------------------------------------------------------------------
/// <summary> Export class. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">             [in,out] If non-null, a lua_State to process. </param>
/// <param name="global_name">   Name of the global. </param>
/// <param name="userdata_name"> Name of the userdata. </param>
/// <param name="functions">     The functions. </param>
///-------------------------------------------------------------------------------------------------
inline void export_class(
    lua_State* l,
    const std::string& global_name,
    const std::string& userdata_name,
    const luaL_Reg*    functions )
{
    if( l && !global_name.empty() && !userdata_name.empty() && functions ) {
        luaL_newmetatable( l, userdata_name.data() );
        luaL_setfuncs( l, functions, 0 );
        lua_pushvalue( l, -1 );
        lua_setfield( l, -1, "__index" );
        lua_setglobal( l, global_name.data() );
    }
}

///-------------------------------------------------------------------------------------------------
/// <summary> Sets global bool. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">     [in,out] If non-null, a lua_State to process. </param>
/// <param name="name">  The name. </param>
/// <param name="value"> True to value. </param>
///-------------------------------------------------------------------------------------------------
inline void set_global_bool(
    lua_State*         l,
    const std::string& name,
    const bool         value )
{
    if( l && !name.empty() ) {
        push_bool( l, value );
        set_global( l, name );
    }
}

///-------------------------------------------------------------------------------------------------
/// <summary> Sets global number. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">     [in,out] If non-null, a lua_State to process. </param>
/// <param name="name">  The name. </param>
/// <param name="value"> The value. </param>
///-------------------------------------------------------------------------------------------------
template<typename T>
void set_global_number(
    lua_State*         l,
    const std::string& name,
    const T            value )
{
    if( l && !name.empty() ) {
        push_number( l, value );
        set_global( l, name );
    }
}

///-------------------------------------------------------------------------------------------------
/// <summary> Sets global integer. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">     [in,out] If non-null, a lua_State to process. </param>
/// <param name="name">  The name. </param>
/// <param name="value"> The value. </param>
///-------------------------------------------------------------------------------------------------
template<typename T>
void set_global_integer(
    lua_State*         l,
    const std::string& name,
    const T            value )
{
    if( l && !name.empty() ) {
        push_integer( l, value );
        set_global( l, name );
    }
}

///-------------------------------------------------------------------------------------------------
/// <summary> Sets global string. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">     [in,out] If non-null, a lua_State to process. </param>
/// <param name="name">  The name. </param>
/// <param name="value"> The value. </param>
///-------------------------------------------------------------------------------------------------
inline void set_global_string(
    lua_State*         l,
    const std::string& name,
    const std::string& value )
{
    if( l && !name.empty() && !value.empty() ) {
        push_string( l, value );
        set_global( l, name );
    }
}

///-------------------------------------------------------------------------------------------------
/// <summary> Gets the stack count. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l"> [in,out] If non-null, a lua_State to process. </param>
///
/// <returns> An int32_t. </returns>
///-------------------------------------------------------------------------------------------------
inline int32_t top( lua_State* l )
{
    return l ? lua_gettop( l ) : -1;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Compares the stack count. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">      [in,out] If non-null, a lua_State to process. </param>
/// <param name="needed"> The needed. </param>
///
/// <returns> True if it succeeds, false if it fails. </returns>
///-------------------------------------------------------------------------------------------------
template<typename T>
bool top( lua_State* l, const T needed )
{
    static_assert( std::is_integral<T>::value, "Type T has to be integral" );
    return static_cast<T>( top( l ) ) == needed;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Compares the stack count. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <typeparam name="T"> Generic type parameter. </typeparam>
/// <param name="l">    [in,out] If non-null, a lua_State to process. </param>
/// <param name="mins"> The mins. </param>
/// <param name="maxs"> The maxs. </param>
///
/// <returns> True if it succeeds, false if it fails. </returns>
///-------------------------------------------------------------------------------------------------
template<typename T>
bool top( lua_State* l, const T mins, const T maxs )
{
    static_assert( std::is_integral<T>::value, "Type T has to be integral" );
    const auto t = static_cast<T>( top( l ) );
    return t >= mins && t <= maxs;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Executes. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="l">           [in,out] If non-null, a lua_State to process. </param>
/// <param name="data">        The data. </param>
/// <param name="from_memory"> (Optional) True to from memory. </param>
///
/// <returns> True if it succeeds, false if it fails. </returns>
///-------------------------------------------------------------------------------------------------
inline bool execute(
    lua_State*         l,
    const std::string& data,
    const bool         from_memory = false )
{
    if( !l || data.empty() ) {
        return false;
    }
    if( !from_memory ) {
        return !luaL_dofile( l, data.data() );
    }
    if( luaL_loadstring( l, data.data() ) > 0 ) {
        return false;
    }
    if( lua_pcall( l, 0, 0, 0 ) > 0 ) {
        lua_pop( l, 1 );
        return false;
    }
    return true;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Gets the directory. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <returns> The directory. </returns>
///-------------------------------------------------------------------------------------------------
inline std::string& get_directory()
{
    static std::string dir;
    return dir;
}

///-------------------------------------------------------------------------------------------------
/// <summary> Initializes a new lua object. </summary>
///
/// <remarks> ReactiioN, 06.07.2017. </remarks>
///
/// <param name="include_directory"> (Optional) Pathname of the include directory. </param>
///
/// <returns> Null if it fails, else a pointer to a lua_State. </returns>
///-------------------------------------------------------------------------------------------------
inline lua_State* initialize( const std::string& include_directory = "" )
{
    if( LUA_VERSION_MAJOR != major_version ) {
        printf( "[easy_lua] invalid major version: %s\n", LUA_VERSION_MAJOR );
        return nullptr;
    }
    if( LUA_VERSION_MINOR != minor_version ) {
        printf( "[easy_lua] invalid minor version: %s\n", LUA_VERSION_MINOR );
        return nullptr;
    }
    if( LUA_VERSION_RELEASE != release_version ) {
        printf( "[easy_lua] invalid release version: %s\n", LUA_VERSION_RELEASE );
        return nullptr;
    }
    
    auto l = luaL_newstate();
    if( !l ) {
        return nullptr;
    }

    auto cur_version = lua_version( l );
    if( !cur_version ) {
        lua_close( l );
        return nullptr;
    }

    /// be sure that we're really using the correct version!
    if( *cur_version != supported_version_number ) {
        lua_close( l );
        return nullptr;
    }

    luaL_openlibs( l );
    if( !include_directory.empty() ) {
        get_directory().assign( include_directory );
        export_function( l, "include", []( lua_State* L ) -> int32_t {
            auto get_current_directory = []( const std::string& appended_file ) -> std::string
            {
                auto path = get_directory();
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
                printf( "[easy_lua] error including lua file: %s", get_string( L, -1 ) );
            }
            return 0;
        } );
    }
    return l;
}

}

#endif
///-------------------------------------------------------------------------------------------------
/// End of easy_lua.hpp
///-------------------------------------------------------------------------------------------------
