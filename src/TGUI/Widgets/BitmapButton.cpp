/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2020 Bruno Van de Velde (vdv_b@tgui.eu)
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


#include <TGUI/Widgets/BitmapButton.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BitmapButton::BitmapButton()
    {
        m_type = "BitmapButton";
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BitmapButton::Ptr BitmapButton::create(const String& text)
    {
        auto button = std::make_shared<BitmapButton>();

        if (!text.empty())
            button->setText(text);

        return button;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BitmapButton::Ptr BitmapButton::copy(BitmapButton::ConstPtr button)
    {
        if (button)
            return std::static_pointer_cast<BitmapButton>(button->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::setSize(const Layout2d& size)
    {
        Button::setSize(size);

        recalculateGlyphSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::setText(const String& text)
    {
        m_string = text;
        m_text.setString(text);
        m_text.setCharacterSize(m_textSize);

        if (m_autoSize && (m_textSize != 0))
            updateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::setImage(const Texture& image)
    {
        m_glyphTexture = image;
        m_glyphSprite.setTexture(m_glyphTexture);
        updateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Texture& BitmapButton::getImage() const
    {
        return m_glyphTexture;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::setImageScaling(float relativeHeight)
    {
        m_relativeGlyphHeight = relativeHeight;
        updateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float BitmapButton::getImageScaling() const
    {
        return m_relativeGlyphHeight;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> BitmapButton::save(SavingRenderersMap& renderers) const
    {
        auto node = Button::save(renderers);
        node->propertyValuePairs["Image"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(m_glyphTexture));
        node->propertyValuePairs["ImageScaling"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(m_relativeGlyphHeight));
        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Button::load(node, renderers);

        if (node->propertyValuePairs["Image"])
            setImage(Deserializer::deserialize(ObjectConverter::Type::Texture, node->propertyValuePairs["Image"]->value).getTexture());
        if (node->propertyValuePairs["ImageScaling"])
            setImageScaling(Deserializer::deserialize(ObjectConverter::Type::Number, node->propertyValuePairs["ImageScaling"]->value).getNumber());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::draw(BackendRenderTargetBase& target, RenderStates states) const
    {
        if (!m_glyphSprite.isSet())
        {
            Button::draw(target, states);
            return;
        }

        // Draw the borders
        if (m_bordersCached != Borders{0})
        {
            target.drawBorders(states, m_bordersCached, getSize(), Color::applyOpacity(getCurrentBorderColor(), m_opacityCached));
            states.transform.translate(m_bordersCached.getOffset());
        }

        // Check if there is a background texture
        if (m_sprite.isSet())
        {
            if (!m_enabled && m_spriteDisabled.isSet())
                target.drawSprite(states, m_spriteDisabled);
            else if (m_mouseHover && m_mouseDown && m_spriteDown.isSet())
                target.drawSprite(states, m_spriteDown);
            else if (m_mouseHover && m_spriteHover.isSet())
                target.drawSprite(states, m_spriteHover);
            else if (m_focused && m_spriteFocused.isSet())
                target.drawSprite(states, m_spriteFocused);
            else
                target.drawSprite(states, m_sprite);
        }
        else // There is no background texture
        {
            target.drawFilledRect(states, getInnerSize(), Color::applyOpacity(getCurrentBackgroundColor(), m_opacityCached));
        }

        target.addClippingLayer(states, {{}, getInnerSize()});
        if (m_text.getString().empty())
        {
            states.transform.translate({(getInnerSize().x - m_glyphSprite.getSize().x) / 2.f, (getInnerSize().y - m_glyphSprite.getSize().y) / 2.f});
            target.drawSprite(states, m_glyphSprite);
        }
        else // There is some text next to the glyph
        {
            const float distanceBetweenTextAndImage = m_text.getSize().y / 5.f;
            const float width = m_glyphSprite.getSize().x + distanceBetweenTextAndImage + m_text.getSize().x;
            states.transform.translate({(getInnerSize().x - width) / 2.f, (getInnerSize().y - m_glyphSprite.getSize().y) / 2.f});
            target.drawSprite(states, m_glyphSprite);
            states.transform.translate({m_glyphSprite.getSize().x + distanceBetweenTextAndImage, (m_glyphSprite.getSize().y - m_text.getSize().y) / 2.f});
            target.drawText(states, m_text);
        }
        target.removeClippingLayer();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::updateSize()
    {
        if (!m_glyphSprite.isSet())
        {
            Button::updateSize();
            return;
        }

        if (m_autoSize)
        {
            Widget::setSize({getSize().x, m_text.getSize().y * 1.25f + m_bordersCached.getTop() + m_bordersCached.getBottom()});

            recalculateGlyphSize();

            if (m_text.getString().empty())
            {
                Widget::setSize({m_glyphSprite.getSize().x + (getInnerSize().y - m_glyphSprite.getSize().y) + m_bordersCached.getLeft() + m_bordersCached.getRight(),
                                 getSize().y});
            }
            else
            {
                const float spaceAroundImageAndText = m_text.getSize().y;
                const float distanceBetweenTextAndImage = m_text.getSize().y / 5.f;
                Widget::setSize({m_glyphSprite.getSize().x + distanceBetweenTextAndImage + m_text.getSize().x
                                + spaceAroundImageAndText + m_bordersCached.getLeft() + m_bordersCached.getRight(), getSize().y});
            }
        }
        else
            recalculateGlyphSize();

        m_bordersCached.updateParentSize(getSize());

        // Reset the texture sizes
        m_sprite.setSize(getInnerSize());
        m_spriteHover.setSize(getInnerSize());
        m_spriteDown.setSize(getInnerSize());
        m_spriteDisabled.setSize(getInnerSize());
        m_spriteFocused.setSize(getInnerSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::recalculateGlyphSize()
    {
        if (!m_glyphSprite.isSet())
            return;

        if (m_relativeGlyphHeight == 0)
            m_glyphSprite.setSize(Vector2f{m_glyphTexture.getImageSize()});
        else
            m_glyphSprite.setSize({m_relativeGlyphHeight * getInnerSize().y,
                                   (m_relativeGlyphHeight * getInnerSize().y) / m_glyphTexture.getImageSize().y * m_glyphTexture.getImageSize().x});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
