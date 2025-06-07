#pragma once
#include "skins.hpp"
#include "interfaces.h"

#define MENU_WIDTH 600
#define MENU_HEIGHT 600

namespace CMenuBase {
    void _DrawMenuOutline(int x, int y, int xx, int yy) {
        I::surface->DrawSetColor(255, 255, 255, 255);
        I::surface->DrawOutlinedRect(x, y, xx, yy);
    }
    void _DrawMenuBase(int x, int y, int xx, int yy) {

        I::surface->DrawSetColor(20, 20, 20, 255);
        I::surface->DrawFilledRect(x, y, xx, yy);
    }
    void _DrawTitleBar(int x, int y, int xx, int yy, int menufont) {

        I::surface->DrawSetColor(255, 87, 34, 255);
        I::surface->DrawFilledRect(x, y, xx, yy);
        auto textsize = I::surface->getTextSize("legacyhook", menufont);
        hk::DrawString(x + 5, y + textsize.y / 2, 255, 255, 255,255, false, "legacyhook", menufont);
    }
}
namespace CMenuElement {

	void Slider(int x, int y, int xx, int yy, HFont font, int& value, int min, int max, const char* text) {
		int x1, x2;
		I::surface->GetCursorPos(x1, x2);
		if (x1 > x && x1 < xx && x2 > y && x2 < yy) {
			if (GetAsyncKeyState(VK_LBUTTON)) {
				value = (x1 - x) / (float)(xx - x) * (max - min) + min;
			}
		}
		I::surface->DrawSetColor(50, 50, 50, 255);
		I::surface->DrawFilledRect(x, y, xx, yy);
		I::surface->DrawSetColor(255, 255, 255, 255);
		I::surface->DrawOutlinedRect(x, y, xx, yy);
		I::surface->DrawSetColor(100, 100, 100, 255);
		I::surface->DrawFilledRect(x + 1, y + 1, x + 1 + (xx - x - 2) * ((value - min) / (float)(max - min)), yy - 1);
		hk::DrawString(x, y - 15, 255, 255, 255, 255, false, text, font);
		hk::DrawString(xx - 3 - strlen(std::to_string(value).c_str()) * 8, y - 15, 255, 255, 255, 255, false, std::to_string(value).c_str(), font);
	}
    void SliderFloat(int x, int y, int xx, int yy, HFont font, float& value, float min, float max, const char* text) {
        int x1, x2;
        I::surface->GetCursorPos(x1, x2);
        if (x1 > x && x1 < xx && x2 > y && x2 < yy) {
            if (GetAsyncKeyState(VK_LBUTTON)) {
                value = (x1 - x) / (float)(xx - x) * (max - min) + min;
            }
        }
        I::surface->DrawSetColor(50, 50, 50, 255);
        I::surface->DrawFilledRect(x, y, xx, yy);
        I::surface->DrawSetColor(255, 255, 255, 255);
        I::surface->DrawOutlinedRect(x, y, xx, yy);
        I::surface->DrawSetColor(100, 100, 100, 255);
        I::surface->DrawFilledRect(x + 1, y + 1, x + 1 + (xx - x - 2) * ((value - min) / (float)(max - min)), yy - 1);
        hk::DrawString(x, y - 15, 255, 255, 255, 255, false, text, font);
        hk::DrawString(xx - 3 - strlen(std::to_string(value).c_str()) * 8, y - 15, 255, 255, 255, 255, false, std::to_string(value).c_str(), font);
    }
    void Checkbox(int x, int y, HFont font, bool& toggle, std::string text) {
        int x1, x2;

        I::surface->GetCursorPos(x1, x2);
        if (x1 > x && x1 < x + 30 && x2 > y && x2 < y + 30) {
            if (GetAsyncKeyState(VK_LBUTTON) & 1) {
                toggle = !toggle;
            }
            I::surface->DrawSetColor(50, 50, 50, 255);
            I::surface->DrawFilledRect(x, y, x + 20, y + 20);

            if (toggle) {
                I::surface->DrawSetColor(255, 102, 0, 255);
                I::surface->DrawFilledRect(x + 3, y + 3, x + 17, y + 17);
            }

        }
        else {
            I::surface->DrawSetColor(40, 40, 40, 255); 
            I::surface->DrawFilledRect(x, y, x + 20, y + 20);

            if (toggle) {
                I::surface->DrawSetColor(255, 102, 0, 255);  
                I::surface->DrawFilledRect(x + 3, y + 3, x + 17, y + 17);  
            }
        }

        auto siz = I::surface->getTextSize(text.c_str(), font);
        hk::DrawString(x + 30, y + 2, 255, 255, 255, 255, false, text.c_str(), font);
    }

    CVector DrawTabs(int x, int y, int menufont) {
        int buttonWidth = (MENU_WIDTH / 4);
        int buttonHeight = 30;
        int buttonX = x;
        int buttonY = y;
        int x1, x2;
        I::surface->GetCursorPos(x1, x2);
        const char* labels[] = { "Aim", "ESP", "Skins", "Misc"};


        int avgCharWidth = 8;

        for (int i = 0; i < 4 ; ++i) {
            I::surface->DrawSetColor(40, 40, 40, 255);
            if (vars::iMenuIndex == i) I::surface->DrawSetColor(245, 92, 0, 255);
			if (x1 > buttonX && x1 < buttonX + buttonWidth && x2 > buttonY && x2 < buttonY + buttonHeight) {
				I::surface->DrawSetColor(255, 87, 34, 255);
				if (GetAsyncKeyState(VK_LBUTTON) & 1) {
					vars::iMenuIndex = i;
					I::surface->DrawSetColor(255, 102, 0, 255);
				}
                
			}
            // i could make it better but fuck it

            I::surface->DrawFilledRect(buttonX, buttonY, buttonX + buttonWidth, buttonY + buttonHeight);



            int textLength = strlen(labels[i]);
            int textWidth = textLength * avgCharWidth;
            int textHeight = 12;

            int textX = buttonX + (buttonWidth - textWidth) / 2;
            int textY = buttonY + (buttonHeight - textHeight) / 2;

            hk::DrawString(textX, textY, 255, 255, 255, 255, false, labels[i], menufont);

            buttonX += buttonWidth;
        }
		return CVector(buttonX, buttonY);
    }
    void SkinTypeButton(int x, int y, int font, ItemDefinitionIndex Weapon) {
        bool toggled = cfg::skins::iSkinsTabSelectedSkin == Weapon;
        auto buttonWidth = (MENU_HEIGHT / 2) - 40;
        auto buttonHeight = 20;
        int x1, x2;
        I::surface->GetCursorPos(x1, x2);
        I::surface->DrawSetColor(40, 40, 40, 255);
        if (toggled) I::surface->DrawSetColor(245, 92, 0, 255);
        if (x1 > x && x1 < x + buttonWidth && x2 > y && x2 < y + buttonHeight) {
            I::surface->DrawSetColor(255, 87, 34, 255);
            if (GetAsyncKeyState(VK_LBUTTON) & 1) {
                cfg::skins::iSkinsTabSelectedSkin = Weapon;
                I::surface->DrawSetColor(255, 102, 0, 255);
            }
        }
        
        I::surface->DrawFilledRect(x + 1, y + 1, x + buttonWidth - 1, y + buttonHeight + 1);
        I::surface->DrawSetColor(255, 255, 255, 255);
        I::surface->DrawLine(x, y + buttonHeight + 1, x + buttonWidth, y + buttonHeight + 1);

        const char* test = nullptr;

        auto it = ItemDefNames.find(Weapon); 
        if (it != ItemDefNames.end()) {
            test = it->second;
        }
        else {
            test = "Unknown Weapon";  
        }
       
        auto size = I::surface->getTextSize(test, font);
        auto textX = x + 5;
        auto textY = y + 2;

        hk::DrawString(textX, textY, 255, 255, 255, 255, false, test, font);

    }
    void SkinButton(int x, int y, int font, ItemDefinitionIndex Weapon, PaintKit skin) {
        bool toggled = false;


        if (skins.find(Weapon) != skins.end()) {
            if (skins[Weapon].paintkit_id == skin.paintkit_id) toggled = true;
        }
        auto buttonWidth = (MENU_HEIGHT / 2); // i cannot imagine how my brain was asleep and why it works but it works
        auto buttonHeight = 20;
        int x1, x2;
        I::surface->GetCursorPos(x1, x2);
        I::surface->DrawSetColor(40, 40, 40, 255);
        if (toggled) I::surface->DrawSetColor(245, 92, 0, 255);
        if (x1 > x && x1 < x + buttonWidth && x2 > y && x2 < y + buttonHeight) {
            I::surface->DrawSetColor(255, 87, 34, 255);
            if (GetAsyncKeyState(VK_LBUTTON) & 1) {
                skins[Weapon] = skin;
                I::surface->DrawSetColor(255, 102, 0, 255);
            }
        }

        I::surface->DrawFilledRect(x + 1, y + 1, x + buttonWidth - 1, y + buttonHeight + 1);
        I::surface->DrawSetColor(255, 255, 255, 255);
        I::surface->DrawLine(x, y + buttonHeight + 1, x + buttonWidth, y + buttonHeight + 1);

        const char* test = nullptr;


        auto textX = x + 5;
        auto textY = y + 2;
        auto res = PaintKitToSkinName(skin);
        if (res == "U")
        {

            hk::DrawString(textX, textY, 255, 255, 255, 255, false, skin.skin_name.c_str(), font);
        }
        else {

            hk::DrawString(textX, textY, 255, 255, 255, 255, false, res, font);
        }

    }
    void KnifeButton(int x, int y, int font, ItemDefinitionIndex KnifeType, bool isCT) {
        bool toggled = false;


        if (isCT) {
            if (KnifeType == CTKnife) toggled = true;
        } else { if (KnifeType == TKnife) toggled = true; }
        auto buttonWidth = 150; // i cannot imagine how my brain was asleep and why it works but it works
        auto buttonHeight = 20;
        int x1, x2;
        I::surface->GetCursorPos(x1, x2);
        I::surface->DrawSetColor(40, 40, 40, 255);
        if (toggled) I::surface->DrawSetColor(245, 92, 0, 255);
        if (x1 > x && x1 < x + buttonWidth && x2 > y && x2 < y + buttonHeight) {
            I::surface->DrawSetColor(255, 87, 34, 255);
            if (GetAsyncKeyState(VK_LBUTTON) & 1) {
                if (isCT) {
                    CTKnife = KnifeType;
                }
                else {
                    TKnife = KnifeType;
                }
                I::surface->DrawSetColor(255, 102, 0, 255);
            }
        }

        I::surface->DrawFilledRect(x + 1, y + 1, x + buttonWidth - 1, y + buttonHeight + 1);
        I::surface->DrawSetColor(255, 255, 255, 255);

        const char* test = nullptr;


        auto textX = x + 5;
        auto textY = y + 2;
        auto it = ItemDefNames.find(KnifeType);
        if (it != ItemDefNames.end()) {
            test = it->second;
        }
        else {
            test = "Unknown Knife";
        }

        hk::DrawString(textX, textY, 255, 255, 255, 255, false, test, font);
        

    }
    void SkinsButtonBack(int x, int y, int font) {
        auto buttonWidth = ((MENU_HEIGHT / 2) - 40) / 2;
        auto buttonHeight = 40;
        int x1, x2;
        I::surface->GetCursorPos(x1, x2);
        I::surface->DrawSetColor(40, 40, 40, 255);
        if (x1 > x && x1 < x + buttonWidth && x2 > y && x2 < y + buttonHeight) {
            I::surface->DrawSetColor(255, 87, 34, 255);
            if (GetAsyncKeyState(VK_LBUTTON) & 1) {
                cfg::skins::iWeaponTypesTab = 0; // the dumbest solution but only one that came to my mind while finding something that wont require handler for shit like equaling to -1 or 2
                I::surface->DrawSetColor(255, 102, 0, 255);
            }
        }

        I::surface->DrawFilledRect(x + 1, y + 1, x + buttonWidth - 1, y + buttonHeight + 1);
        I::surface->DrawSetColor(255, 255, 255, 255);
        I::surface->DrawLine(x, y, x, y + buttonHeight);
        I::surface->DrawLine(x, y + buttonHeight, x + buttonWidth, y + buttonHeight);

        const char* test = nullptr;


        auto textX = x + 3;
        auto textY = y + 2;

        hk::DrawString(textX, textY, 255, 255, 255, 255, false, "Previous", font);
    }
    void SkinsButtonForward(int x, int y, int font) {
        auto buttonWidth = (((MENU_HEIGHT / 2) - 40) / 2) - 1;
        auto buttonHeight = 40;
        int x1, x2;
        I::surface->GetCursorPos(x1, x2);
        I::surface->DrawSetColor(40, 40, 40, 255);
        if (x1 > x && x1 < x + buttonWidth && x2 > y && x2 < y + buttonHeight) {
            I::surface->DrawSetColor(255, 87, 34, 255);
            if (GetAsyncKeyState(VK_LBUTTON) & 1) {
                cfg::skins::iWeaponTypesTab = 1; // the dumbest solution but only one that came to my mind while finding something that wont require handler for shit like equaling to -1 or 2
                I::surface->DrawSetColor(255, 102, 0, 255);
            }
        }

        I::surface->DrawFilledRect(x, y + 1, x + buttonWidth, y + buttonHeight);
        I::surface->DrawSetColor(255, 255, 255, 255);
        I::surface->DrawLine(x, y + buttonHeight, x + buttonWidth, y + buttonHeight);
        I::surface->DrawLine(x + buttonWidth, y, x + buttonWidth, y + buttonHeight);
        const char* test = nullptr;


        auto textX = x + 5;
        auto textY = y + 2;

        hk::DrawString(textX, textY, 255, 255, 255, 255, false, "Next", font);
    }
}
namespace CMenu {
    void Draw(HFont menufont, HFont CheckboxFont) {

		int w, h; I::engine->GetScreenSize(w, h);

		CVector NextPos = CVector((w / 2 - MENU_WIDTH / 2), (h / 2 - MENU_HEIGHT / 2));

        CMenuBase::_DrawMenuBase(w / 2 - MENU_WIDTH / 2, h / 2 - MENU_HEIGHT / 2, w / 2 + MENU_WIDTH / 2, h / 2 + MENU_HEIGHT / 2);

		CMenuBase::_DrawTitleBar(w / 2 - MENU_WIDTH / 2, h / 2 - MENU_HEIGHT / 2, w / 2 + MENU_WIDTH / 2, h / 2 - MENU_HEIGHT / 2 + 30, menufont);


        I::surface->DrawSetColor(30, 30, 30, 255);
        I::surface->DrawFilledRect((w / 2 - MENU_WIDTH / 2), (h / 2 - MENU_HEIGHT / 2) + 30, (w / 2 - MENU_WIDTH / 2) + MENU_WIDTH, (h / 2 - MENU_HEIGHT / 2) + 60);
		auto r1 = CMenuElement::DrawTabs((w / 2 - MENU_WIDTH / 2), (h / 2 - MENU_HEIGHT / 2) + 30, menufont);
        NextPos.y = r1.y + 40;
        NextPos.x += 10;
        I::surface->DrawSetColor(255, 255, 255, 255);
        I::surface->DrawLine(NextPos.x - 10, NextPos.y - 10, NextPos.x + MENU_WIDTH - 10, NextPos.y - 10);

       
       
        
        switch (vars::iMenuIndex) {
            case 0: {
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::aim::bIsEnabled, "Aimbot");
                NextPos.y += 40;
                CMenuElement::SliderFloat(NextPos.x, NextPos.y + 5, NextPos.x + 150, NextPos.y + 15, CheckboxFont, cfg::aim::flAimbotFov, 0.1, 180, "Aimbot Fov");
                NextPos.y += 40;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::aim::bUseAutofire, "Autofire");
                NextPos.y += 40;
                CMenuElement::SliderFloat(NextPos.x, NextPos.y + 5, NextPos.x + 150, NextPos.y + 15, CheckboxFont, cfg::aim::flMaxInaccurracy, 0, 100, "Hit Chance");
                NextPos.y += 40;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::aim::bSilentAim, "Silent Aim");
                NextPos.y += 40;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::aim::bAntiAim, "Anti Aim");
                NextPos.y += 40;
                CMenuElement::Slider(NextPos.x, NextPos.y + 5, NextPos.x + 150, NextPos.y + 15, CheckboxFont, cfg::aim::iAntiAimSpeed, 1, 45, "AA Speed");
                break;
            }
            case 1: {
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::esp::bBoxEsp, "Box ESP");
                NextPos.y += 30;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::esp::bHealthBar, "Health Bar");
                NextPos.y += 30;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::esp::bThirdPerson, "Third Person");
                NextPos.y += 30;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::esp::bDrawVelocity, "Draw Velocity");
                NextPos.y += 30;
                if (cfg::esp::bDrawVelocity) {
                    NextPos.y += 10;
                    CMenuElement::Slider(NextPos.x, NextPos.y + 5, NextPos.x + 150, NextPos.y + 15, CheckboxFont, cfg::esp::iVelocityYPos, 1, 300, "Velocity Y Pos");
                }
                break;
            }
            case 2: {

                auto oldpos = NextPos.x + MENU_WIDTH / 2 - 20;
                I::surface->DrawOutlinedRect(NextPos.x, NextPos.y, NextPos.x + MENU_WIDTH / 2 - 40, (h / 2 + MENU_HEIGHT / 2) - 45);
                I::surface->DrawOutlinedRect(NextPos.x + MENU_WIDTH / 2 - 20, NextPos.y, NextPos.x + MENU_WIDTH - 20, (h / 2 + MENU_HEIGHT / 2) - 10);

                if (cfg::skins::iWeaponTypesTab == 0) {
                    for (int i2 = 0; i2 < 23; i2++) {

                        CMenuElement::SkinTypeButton(NextPos.x, NextPos.y, CheckboxFont, skinnableitems[i2]);
                        NextPos.y += 21;
                    }
                }
                else {
                    for (int i2 = 23; i2 < skinnableitems_amount; i2++) {

                        CMenuElement::SkinTypeButton(NextPos.x, NextPos.y, CheckboxFont, skinnableitems[i2]);
                        NextPos.y += 21;
                    }
                }
                NextPos.y = (h / 2 + MENU_HEIGHT / 2) - 45;
                CMenuElement::SkinsButtonBack(NextPos.x, NextPos.y, CheckboxFont);
                NextPos.x += ((MENU_HEIGHT / 2) - 40) / 2;
                CMenuElement::SkinsButtonForward(NextPos.x, NextPos.y, CheckboxFont);
                // draw skins for weapon
                NextPos.x = oldpos;
                NextPos.y = r1.y + 40;;
                for (int i = 0; i < paintkits.size(); i++)
                {
                    if (paintkits.at(i).weapon_type == cfg::skins::iSkinsTabSelectedSkin) {
                        CMenuElement::SkinButton(NextPos.x, NextPos.y, CheckboxFont, (ItemDefinitionIndex)cfg::skins::iSkinsTabSelectedSkin, paintkits.at(i));
                        NextPos.y += 21;
                    }
                }
                break;
            }
            case 3: {
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::movement::bBunnyHop, "Bhop");
                NextPos.y += 30;
				CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::movement::bAutoStrafe, "Auto Strafe"); // temporarily hidden because broken
                NextPos.y += 30;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::misc::bCustomCrosshair, "Custom Crosshair");
                if (cfg::misc::bCustomCrosshair) {

                    NextPos.y += 35;
                    CMenuElement::Slider(NextPos.x, NextPos.y + 5, NextPos.x + 150, NextPos.y + 15, CheckboxFont, cfg::misc::iCustomCrosshairSize, 1, 10, "Size");
                }

                NextPos.y += 30;
                I::surface->DrawSetColor(255, 255, 255, 255); 
                hk::DrawString(NextPos.x, NextPos.y, 255, 255, 255, 255, false, "T Knife", CheckboxFont);
                NextPos.y += 20;
                I::surface->DrawOutlinedRect(NextPos.x, NextPos.y, NextPos.x + 150, NextPos.y + 128);
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_BAYONET, false);
                NextPos.y += 21;
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_BUTTERFLY, false);
                NextPos.y += 21;
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_FLIP, false);
                NextPos.y += 21;
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_GUT, false);
                NextPos.y += 21;
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_KARAMBIT, false);
                NextPos.y += 21;
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_M9_BAYONET, false);
                NextPos.y += 21;
                hk::DrawString(NextPos.x, NextPos.y, 255, 255, 255, 255, false, "CT Knife", CheckboxFont);
                NextPos.y += 20;
                I::surface->DrawOutlinedRect(NextPos.x, NextPos.y, NextPos.x + 150, NextPos.y + 128);
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_BAYONET, true);
                NextPos.y += 21;
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_BUTTERFLY, true);
                NextPos.y += 21;
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_FLIP, true);
                NextPos.y += 21;
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_GUT, true);
                NextPos.y += 21;
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_KARAMBIT, true);
                NextPos.y += 21;
                CMenuElement::KnifeButton(NextPos.x, NextPos.y, CheckboxFont, WEAPON_KNIFE_M9_BAYONET, true);
                NextPos.y += 21;
                break;
            }
        }

        CMenuBase::_DrawMenuOutline(w / 2 - MENU_WIDTH / 2, h / 2 - MENU_HEIGHT / 2, w / 2 + MENU_WIDTH / 2, h / 2 + MENU_HEIGHT / 2);
    }

    void DrawSkinChanger(HFont menufont) {

        /*nt w, h; I::engine->GetScreenSize(w, h);

        CVector NextPos = CVector((w / 2 + 250), (h / 2 - MENU_HEIGHT / 2));

        CMenuBase::_DrawMenuBase((w / 2)+ 250, (h / 2 - MENU_HEIGHT / 2), (w / 2 + MENU_WIDTH / 2) + 400, h / 2 + MENU_HEIGHT / 2);

        CMenuBase::_DrawTitleBar((w / 2) + 250, (h / 2 - MENU_HEIGHT / 2), (w / 2 + MENU_WIDTH / 2) + 400, (h / 2) + 20, menufont);





        CMenuBase::_DrawMenuOutline((w / 2) + 250, (h / 2 - MENU_HEIGHT / 2), (w / 2 + MENU_WIDTH / 2) +400, h / 2 + MENU_HEIGHT / 2);*/
    }

    
}