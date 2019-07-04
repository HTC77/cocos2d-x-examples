//
//  ToggleButton.h
//
//  Created by Branislav Siarsky on 28/03/2016.
//  Copyright © 2016 Smartdone GmbH. All rights reserved.
//

#ifndef ToggleButton_h
#define ToggleButton_h

#include "ui/UIButton.h"
#include "base/CCTouch.h"
#include "base/CCEvent.h"

USING_NS_CC;

class ToggleButton : public cocos2d::ui::Button{
    bool _toggle;
    std::string _normalImageDisabled;
    std::string _selectedImageDisabled;
    TextureResType _texType;

    bool revertToggle();
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);

    void setNormalImageDisabled(std::string normalImageDisabled);
    void setSelectedImageDisabled(std::string selectedImageDisabled);

public:
    ToggleButton();
    virtual ~ToggleButton();
    bool isToggle();
    void setToggle(bool toggle);
    virtual void setEnabled(bool enabled);
    void setHighlighted(bool highlight);
    static ToggleButton* create(const std::string& normalImage,
                                const std::string& selectedImage,
                                const std::string& normalImageDisabled,
                                const std::string& selectedImageDisabled);
    virtual bool init(const std::string& normalImage,
                      const std::string& selectedImage,
                      const std::string& normalImageDisabled,
                      const std::string& selectedImageDisabled);
};

#endif /* ToggleButton_h */
