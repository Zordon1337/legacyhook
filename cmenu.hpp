#pragma once
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
                NextPos.y += 25;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::aim::bUseAutofire, "Autofire");
                NextPos.y += 30;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::aim::bSilentAim, "Silent Aim");
                NextPos.y += 30;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::aim::bAntiAim, "Anti Aim");
                NextPos.y += 40;
                CMenuElement::Slider(NextPos.x, NextPos.y + 5, NextPos.x + 150, NextPos.y + 15, CheckboxFont, cfg::aim::iAntiAimSpeed, 1, 15, "AA Speed");
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

            }
            case 3: {
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::movement::bBunnyHop, "Bhop");
                NextPos.y += 30;
				CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::movement::bAutoStrafe, "Auto Strafe"); // temporarily hidden because broken
                NextPos.y += 30;
                CMenuElement::Checkbox(NextPos.x, NextPos.y + 5, CheckboxFont, cfg::misc::bSniperCrosshair, "Sniper Crosshair");
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