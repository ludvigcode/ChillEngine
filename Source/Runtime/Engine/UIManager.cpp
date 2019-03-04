#include "UIManager.hpp"
#include "Math/Math.hpp"
#include "RenderManager.hpp"
#include "SpriteRenderer.hpp"
#include "TextRenderer.hpp"
#include "UI/UICanvas.hpp"
#include "UI/UIImage.hpp"
#include "UI/UIText.hpp"

#include <iostream>

namespace chill
{
UIManager::UIManager(RenderManager* pRenderManager)
    : m_pRoot(nullptr)
{
    m_pSpriteRenderer = pRenderManager->GetRenderer<SpriteRenderer>();
    m_pTextRenderer = pRenderManager->GetRenderer<TextRenderer>();
}

UIManager::~UIManager()
{
}

UIImage* UIManager::GetImage(const std::string& id)
{
    return nullptr;
}

bool UIManager::LoadUI(const std::string& filename)
{
    YNodeMap* pRoot = static_cast<YNodeMap*>(YNode::Load(filename));
    if (!pRoot)
    {
        return false;
    }

    m_pRoot = Load(pRoot);

    return true;
}

void UIManager::Render()
{
    Render(m_pRoot);
}

UIWidget* UIManager::Load(YNodeMap* pNode)
{
    YNodeValue* pType = pNode->GetChild<YNodeValue>("type");

    UIWidget* pWidget = nullptr;
    if (pType->AsString() == "canvas")
    {
        pWidget = new UICanvas();
    }
    else if (pType->AsString() == "image")
    {
        pWidget = new UIImage();
    }
    else if (pType->AsString() == "text")
    {
        pWidget = new UIText();
    }

    YNodeMap* pTransform = pNode->GetChild<YNodeMap>("transform");
    if (pTransform)
    {
        YNodeValue* pAnchorX = pTransform->GetChild<YNodeValue>("anchor.x");
        if (pAnchorX)
        {
            pWidget->m_anchor.x = pAnchorX->AsFloat();
        }

        YNodeValue* pAnchorY = pTransform->GetChild<YNodeValue>("anchor.x");
        if (pAnchorY)
        {
            pWidget->m_anchor.y = pAnchorY->AsFloat();
        }

        YNodeValue* pPivotX = pTransform->GetChild<YNodeValue>("pivot.x");
        if (pPivotX)
        {
            pWidget->m_pivot.x = pPivotX->AsFloat();
        }

        YNodeValue* pPivotY = pTransform->GetChild<YNodeValue>("pivot.y");
        if (pPivotY)
        {
            pWidget->m_pivot.y = pPivotY->AsFloat();
        }

        YNodeValue* pPositionX = pTransform->GetChild<YNodeValue>("position.x");
        if (pPositionX)
        {
            pWidget->m_position.x = pPositionX->AsFloat();
        }

        YNodeValue* pPositionY = pTransform->GetChild<YNodeValue>("position.y");
        if (pPositionY)
        {
            pWidget->m_position.y = pPositionY->AsFloat();
        }

        YNodeValue* pWidth = pTransform->GetChild<YNodeValue>("width");
        if (pWidth)
        {
            pWidget->m_width = pWidth->AsFloat();
        }

        YNodeValue* pHeight = pTransform->GetChild<YNodeValue>("height");
        if (pHeight)
        {
            pWidget->m_height = pHeight->AsFloat();
        }

        YNodeValue* pEnabled = pTransform->GetChild<YNodeValue>("enabled");
        if (pEnabled)
        {
            pWidget->m_enabled = pEnabled->AsBool();
        }
    }

    YNodeMap* pInfo = pNode->GetChild<YNodeMap>(pType->AsString());
    if (pInfo)
    {
        pWidget->Load(pInfo);
    }

    YNodeArray* pChildren = pNode->GetChild<YNodeArray>("children");
    if (pChildren)
    {
        for (int32 i = 0; i < pChildren->GetChildCount(); ++i)
        {
            YNodeMap* pChild = pChildren->GetChild<YNodeMap>(i);
            if (pChild)
            {
                pWidget->m_children.push_back(Load(pChild));
            }
        }
    }

    return pWidget;
}

void UIManager::Render(UIWidget* pWidget)
{
    if (!pWidget->m_enabled)
    {
        return;
    }

    int32 width = 800.0f;
    int32 height = 600.0f;

    switch (pWidget->GetType())
    {
    case UIWidget::Type::CANVAS:
    {
        break;
    }
    case UIWidget::Type::IMAGE:
    {
        UIImage* pImage = static_cast<UIImage*>(pWidget);
        Vector2f position = pImage->m_position;

        Recti distRect;
        distRect.x = position.x;
        distRect.y = position.y;
        distRect.w = pImage->m_width;
        distRect.h = pImage->m_height;

        m_pSpriteRenderer->Submit(LinearColor(0.0f, 1.0f, 1.0f, 1.0f), distRect);

        break;
    }
    case UIWidget::Type::TEXT:
        break;
    default:
        break;
    }

    for (UIWidget* pW : pWidget->m_children)
    {
        Render(pW);
    }
}
} // namespace chill