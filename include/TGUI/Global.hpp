/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TGUI_DEFINES_HPP
#define TGUI_DEFINES_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TGUI/Config.hpp>
#include <TGUI/Borders.hpp>
#include <TGUI/Exception.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Namespace that contains all TGUI functions and classes
namespace tgui
{
    class Texture;

    /// @internal The internal clipboard that widgets use
    class Clipboard;
    extern TGUI_API Clipboard TGUI_Clipboard;

    /// @internal When disabling the tab key usage, pressing tab will no longer focus another widget.
    extern TGUI_API bool TGUI_TabKeyUsageEnabled;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const float pi = 3.14159265358979f;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief A list of all widget types.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class WidgetType
    {
        Unknown,
        ClickableWidget,
        Picture,
        Button,
        Checkbox,
        RadioButton,
        Label,
        EditBox,
        ListBox,
        ComboBox,
        Slider,
        Scrollbar,
        ProgressBar,
        TextBox,
        SpriteSheet,
        AnimatedPicture,
        SpinButton,
        Slider2d,
        Tab,
        MenuBar,
        ChatBox,
        Knob,
        Tooltip,
        Canvas,
        Panel,
        ChildWindow,
        Grid,
        MessageBox
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    std::string to_string(T value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief While tab key usage is enabled (default), pressing tab will focus another widget.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void enableTabKeyUsage();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief When disabling the tab key usage, pressing tab will no longer focus another widget.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void disableTabKeyUsage();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Set a new resource path.
    ///
    /// This pathname is placed in front of every filename that is used to load a resource.
    ///
    /// @param path  New resource path
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void setResourcePath(const std::string& path);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Return the resource path.
    ///
    /// This pathname is placed in front of every filename that is used to load a resource.
    ///
    /// @return The current resource path
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API const std::string& getResourcePath();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    // Check if two floats are equal, with regard to a small epsilon margin.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API bool compareFloats(float x, float y);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    // Check if a character is a whitespace character.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API bool isWhitespace(char character);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    // Convert a string to an integer. Acts like std::stoi which isn't supported in MinGW TDM.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API int stoi(const std::string& value);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    // Convert a string to a float. Acts like std::stof which isn't supported in MinGW TDM.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API float stof(const std::string& value);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    // Convert a string to an unsigned int. Acts like std::stoul which isn't supported in MinGW TDM.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API unsigned long stoul(const std::string& value);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    // Extract a bool from a string value.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API bool extractBoolFromString(const std::string& property, const std::string& value);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    // Extract a color from a string value. The string must look like: "(r, g, b)" or "(r, g, b, a)".
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API sf::Color extractColorFromString(const std::string& property, const std::string& value);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    // Extract a tgui::Borders from a string. The string must look like: "(left, top, right, bottom)".
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API Borders extractBordersFromString(const std::string& property, const std::string& value);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    // Extract a texture from a string value.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void extractTextureFromString(const std::string& property, const std::string& value, const std::string& rootPath, Texture& texture);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    // Converts a string to lowercase.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API std::string toLower(std::string str);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_DEFINES_HPP

