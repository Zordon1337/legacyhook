#pragma once
#include "interfaces.h"

namespace CMenu {
    void Draw(HFont menufont) {
        I::surface->DrawSetColor(0, 0, 0, 255);
        I::surface->DrawFilledRect(10, 10, 400, 500);

        I::surface->DrawSetColor(50, 50, 50, 255);
        I::surface->DrawFilledRect(10, 10, 400, 35);
        hk::DrawString(15, 15, 255, 255, 255, 255, false, "legacyhook", menufont);


        int buttonWidth = 133;
        int buttonHeight = 40;  
        int buttonX = 10;
        int buttonY = 35;

        const char* labels[] = { "Aim", "ESP", "Misc" };

        
        int avgCharWidth = 8; 

        for (int i = 0; i < 3; ++i) {
            I::surface->DrawSetColor(75, 75, 75, 255);
            I::surface->DrawFilledRect(buttonX, buttonY, buttonX + buttonWidth, buttonY + buttonHeight);

            int textLength = strlen(labels[i]);  
            int textWidth = textLength * avgCharWidth; 
            int textHeight = 12;  

            int textX = buttonX + (buttonWidth - textWidth) / 2;  
            int textY = buttonY + (buttonHeight - textHeight) / 2; 

            hk::DrawString(textX, textY, 255, 255, 255, 255, false, labels[i], menufont);

            buttonX += buttonWidth;
        }

        Checkbox(15, 50, menufont);

        I::surface->DrawSetColor(255, 255, 255, 255);
        I::surface->DrawOutlinedRect(10, 10, 400, 500);
    }

    void Checkbox(int x, int y, HFont font) {
        I::surface->DrawSetColor(200, 200, 200);
        I::surface->DrawFilledRect(x, y, x + 10, x + 10);
        hk::DrawString(x + 20, y + 5, 255, 255, 255, 255, false, "testbox", font);
    }
}