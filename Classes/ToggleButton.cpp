//
//  ToggleButton.cpp
//
//  Created by Branislav Siarsky on 28/03/2016.
//  Copyright © 2016 Smartdone GmbH. All rights reserved.
//

#include "ToggleButton.h"
#include "2d/CCSpriteFrameCache.h"
#include "2d/CCCamera.h"

ToggleButton* ToggleButton::create(const std::string& normalImage,
                            const std::string& selectedImage,
                            const std::string& normalImageDisabled,
                            const std::string& selectedImageDisabled){
    ToggleButton *btn = new (std::nothrow) ToggleButton;
    if (btn && btn->init(normalImage, selectedImage, normalImageDisabled, selectedImageDisabled)){
        btn->autorelease();
    } else {
        CC_SAFE_DELETE(btn);
        btn = nullptr;
    }
    return btn;
}

bool ToggleButton::init(const std::string& normalImage,
                  const std::string& selectedImage,
                  const std::string& normalImageDisabled,
                  const std::string& selectedImageDisabled){

    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(normalImage);
    if (spriteFrame != nullptr){
        _texType = TextureResType::PLIST;
    }

    bool retBool = ui::Button::init(normalImage, selectedImage, "", _texType);
    setNormalImageDisabled(normalImageDisabled);
    setSelectedImageDisabled(selectedImageDisabled);
    return retBool;
}

ToggleButton::ToggleButton() : cocos2d::ui::Button(){
    _toggle = false;
    _normalImageDisabled = "";
    _selectedImageDisabled = "";
    _texType = TextureResType::LOCAL;
}

ToggleButton::~ToggleButton(){
}

void ToggleButton::setNormalImageDisabled(std::string normalImageDisabled){
    _normalImageDisabled = normalImageDisabled;
}

void ToggleButton::setSelectedImageDisabled(std::string selectedImageDisabled){
    _selectedImageDisabled = selectedImageDisabled;
}

bool ToggleButton::revertToggle(){
    setToggle(!_toggle);
    return _toggle;
}

bool ToggleButton::isToggle(){
    return _toggle;
}

void ToggleButton::setToggle(bool toggle){
    if (toggle == _toggle){
        return;
    }
    _toggle = toggle;
    setHighlighted(_toggle);
}

void ToggleButton::setHighlighted(bool highlight){
    if (highlight == _highlight){
        return;
    }
    
    _highlight = highlight;
    if (_highlight){
        setBrightStyle(BrightStyle::HIGHLIGHT);
    }
    else{
        setBrightStyle(BrightStyle::NORMAL);
    }
}

void ToggleButton::setEnabled(bool enabled){
    if (enabled == _enabled){
        return;
    }

    std::string disabledImage;
    if (!enabled){
        if (isToggle()){
            disabledImage = _selectedImageDisabled;
        } else {
            disabledImage = _normalImageDisabled;
        }
        loadTextureDisabled(disabledImage, _texType);
    }
    Widget::setEnabled(enabled);
}

bool ToggleButton::onTouchBegan(Touch *touch, Event *unusedEvent){
    _hitted = false;
    if (isVisible() && isEnabled() && isAncestorsEnabled() && isAncestorsVisible(this)){
        _touchBeganPosition = touch->getLocation();
        auto camera = Camera::getVisitingCamera();
        if(hitTest(_touchBeganPosition, camera, nullptr)){
            if (isClippingParentContainsPoint(_touchBeganPosition)) {
                _hittedByCamera = camera;
                _hitted = true;
            }
        }
    }
    if (_hitted){
        revertToggle();
        /*
         * Propagate touch events to its parents
         */
        if (_propagateTouchEvents){
            this->propagateTouchEvent(TouchEventType::BEGAN, this, touch);
        }
        pushDownEvent();
    }
    return _hitted;
}

void ToggleButton::onTouchMoved(Touch *touch, Event *unusedEvent){
    /*
     * Propagate touch events to its parents
     */
    if (_propagateTouchEvents){
        this->propagateTouchEvent(TouchEventType::MOVED, this, touch);
    }
    
    moveEvent();
}

void ToggleButton::onTouchEnded(Touch *touch, Event *unusedEvent){
    _touchEndPosition = touch->getLocation();
    
    /*
     * Propagate touch events to its parents
     */
    if (_propagateTouchEvents){
        this->propagateTouchEvent(TouchEventType::ENDED, this, touch);
    }
    
    bool highlight = _highlight;
    if (highlight){
        releaseUpEvent();
    }
    else{
        cancelUpEvent();
    }
}

void ToggleButton::onTouchCancelled(Touch *touch, Event *unusedEvent){
    revertToggle();
    cancelUpEvent();
}


