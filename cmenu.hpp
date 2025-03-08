#pragma once
#include "interfaces.h"

#define MENU_WIDTH 400
#define MENU_HEIGHT 500

namespace CMenuBase {
    void _DrawMenuOutline(int x, int y, int xx, int yy) {
        I::surface->DrawSetColor(255, 255, 255, 255);
        I::surface->DrawOutlinedRect(x, y, xx, yy);
    }
    void _DrawMenuBase(int x, int y, int xx, int yy) {

        I::surface->DrawSetColor(0, 0, 0, 255);
        I::surface->DrawFilledRect(x, y, xx, yy);
    }
    void _DrawTitleBar(int x, int y, int xx, int yy, int menufont) {

        I::surface->DrawSetColor(50, 50, 50, 255);
        I::surface->DrawFilledRect(x, y, xx, yy);
        hk::DrawString(x + 5, y + 5, 255, 255, 255, 255, false, "legacyhook", menufont);
    }
}
namespace CMenuElement {

	void Slider(int x, int y, int xx, int yy, HFont font, int& value, int min, int max, const char* text) {
		int x1, x2;
		I::surface->GetCursorPos(x1, x2);
		if (x1 > x && x1 < xx && x2 > y && x2 < yy) {
			if (GetAsyncKeyState(VK_LBUTTON) & 1) {
				value = (x1 - x) / (float)(xx - x) * (max - min) + min;
			}
		}
		I::surface->DrawSetColor(50, 50, 50, 255);
		I::surface->DrawFilledRect(x, y, xx, yy);
		I::surface->DrawSetColor(255, 255, 255, 255);
		I::surface->DrawOutlinedRect(x, y, xx, yy);
		I::surface->DrawSetColor(100, 100, 100, 255);
		I::surface->DrawFilledRect(x + 1, y + 1, x + 1 + (xx - x - 2) * ((value - min) / (float)(max - min)), yy - 1);
		hk::DrawString(x + 5, y - 15, 255, 255, 255, 255, false, text, font);
		hk::DrawString(xx - 5 - strlen(std::to_string(value).c_str()) * 8, y - 15, 255, 255, 255, 255, false, std::to_string(value).c_str(), font);
	}

    void Checkbox(int x, int y, HFont font, bool& toggle, const char* text) {
        int x1, x2;

		I::surface->GetCursorPos(x1, x2);


		if (x1 > x && x1 < x + 15 && x2 > y && x2 < y + 15) {
			if (GetAsyncKeyState(VK_LBUTTON) & 1) {
                toggle = !toggle;
			}
            if (toggle) {
                I::surface->DrawSetColor(50, 150, 255, 255);
            }
            else {
                I::surface->DrawSetColor(200, 200, 255, 255);
            }
		}
		else {
            if (toggle) {
                I::surface->DrawSetColor(30, 120, 220, 255);
            }
            else {
                I::surface->DrawSetColor(180, 180, 180, 255);
            }
		}
        I::surface->DrawFilledRect(x, y, x + 15, y + 15);
        hk::DrawString(x + 20, y, 255, 255, 255, 255, false, text, font);
    }
    CVector DrawTabs(int x, int y, int menufont) {
        int buttonWidth = 133;
        int buttonHeight = 40;
        int buttonX = x;
        int buttonY = y;
        int x1, x2;
        I::surface->GetCursorPos(x1, x2);
        const char* labels[] = { "Aim", "ESP", "Misc" };


        int avgCharWidth = 8;

        for (int i = 0; i < 3; ++i) {
            I::surface->DrawSetColor(75, 75, 75, 255);

			if (x1 > buttonX && x1 < buttonX + buttonWidth && x2 > buttonY && x2 < buttonY + buttonHeight) {
				I::surface->DrawSetColor(100, 100, 100, 255);
				if (GetAsyncKeyState(VK_LBUTTON) & 1) {
					vars::iMenuIndex = i;
					I::surface->DrawSetColor(50, 50, 50, 255);
				}
			}

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
    void Draw(HFont menufont) {

		int w, h; I::engine->GetScreenSize(w, h);

		CVector NextPos = CVector((w / 2 - MENU_WIDTH / 2), (h / 2 - MENU_HEIGHT / 2));

        CMenuBase::_DrawMenuBase(w / 2 - MENU_WIDTH / 2, h / 2 - MENU_HEIGHT / 2, w / 2 + MENU_WIDTH / 2, h / 2 + MENU_HEIGHT / 2);

		CMenuBase::_DrawTitleBar(w / 2 - MENU_WIDTH / 2, h / 2 - MENU_HEIGHT / 2, w / 2 + MENU_WIDTH / 2, h / 2 - MENU_HEIGHT / 2 + 20, menufont);

		auto r1 = CMenuElement::DrawTabs((w / 2 - MENU_WIDTH / 2), (h / 2 - MENU_HEIGHT / 2) + 20, menufont);
        NextPos.y = r1.y + 40;
        

       
       
        
        switch (vars::iMenuIndex) {
            case 0: {
                CMenuElement::Checkbox(NextPos.x + 5, NextPos.y + 5, menufont, cfg::aim::bIsEnabled, "Aimbot");
                NextPos.y += 20;
                CMenuElement::Checkbox(NextPos.x + 5, NextPos.y + 5, menufont, cfg::aim::bUseAutofire, "Autofire");
                NextPos.y += 20;
                CMenuElement::Checkbox(NextPos.x + 5, NextPos.y + 5, menufont, cfg::aim::bAntiAim, "Anti Aim");
                NextPos.y += 30;
                CMenuElement::Slider(NextPos.x + 5, NextPos.y + 5, NextPos.x + 150, NextPos.y + 20, menufont, cfg::aim::iAntiAimSpeed, 1, 15, "AA Speed");
                break;
            }
            case 1: {
                CMenuElement::Checkbox(NextPos.x + 5, NextPos.y + 5, menufont, cfg::esp::bBoxEsp, "Box ESP");
                NextPos.y += 20;
                CMenuElement::Checkbox(NextPos.x + 5, NextPos.y + 5, menufont, cfg::esp::bHealthBar, "Health Bar");
                NextPos.y += 20;
                break;
            }
            case 2: {
                CMenuElement::Checkbox(NextPos.x + 5, NextPos.y + 5, menufont, cfg::movement::bBunnyHop, "Bhop");
                NextPos.y += 20;
				//CMenuElement::Checkbox(NextPos.x + 5, NextPos.y + 5, menufont, cfg::movement::bAutoStrafe, "Auto Strafe"); // temporarily hidden because broken
                break;
            }
        }

        CMenuBase::_DrawMenuOutline(w / 2 - MENU_WIDTH / 2, h / 2 - MENU_HEIGHT / 2, w / 2 + MENU_WIDTH / 2, h / 2 + MENU_HEIGHT / 2);
    }

  

    
}