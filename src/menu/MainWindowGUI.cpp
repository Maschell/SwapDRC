/****************************************************************************
 * Copyright (C) 2015 Dimok
 * Modified by Maschell, 2017 for SWAP DRC
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#include "MainWindowGUI.h"
#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/socket_functions.h"
#include "Application.h"
#include "utils/StringTools.h"
#include "utils/logger.h"

MainWindowGUI::MainWindowGUI(s32 w, s32 h)
    : GuiFrame(w, h)
    , width(w)
    , height(h)
    , bgImageColor(w, h, (GX2Color){ 0, 0, 0, 0 }){

    bgImageColor.setImageColor((GX2Color){  248, 249, 248, 255 }, 0);
    bgImageColor.setImageColor((GX2Color){  248, 249, 248, 255 }, 1);
    bgImageColor.setImageColor((GX2Color){  248, 249, 248, 255 }, 2);
    bgImageColor.setImageColor((GX2Color){ 248, 249, 248, 255 }, 3);
    append(&bgImageColor);

    headLine.setText(gettext("Swap DRC!"));
    headLine.setFontSize(50);
    headLine.setAlignment(ALIGN_TOP_CENTER);
    headLine.setPosition(0,-110);
    headLine.setColor(glm::vec4(0.3f,0.3f,0.3f,1.0f));
    append(&headLine);

    //Copy paste from dimok's code. Thanks <3
    GuiText *text = NULL;

    f32 positionY = 210.0f;
    f32 positionX = 40.0f;
    f32 positionX2 = 250.0f;
    f32 positionX3 = 80.0f;

    s32 fontSize = 28;
    glm::vec4 textColor = glm::vec4(0.3f,0.3f,0.3f,1.0f);

    text = new GuiText(gettext("Press + to apply"), fontSize, textColor);
    text->setPosition(positionX, positionY);
    text->setAlignment(ALIGN_LEFT | ALIGN_MIDDLE);
    aboutText.push_back(text);
    append(text);

    positionY -= 35;

    text = new GuiText(gettext("Press Home to return to HBL"), fontSize, textColor);
    text->setPosition(positionX, positionY);
    text->setAlignment(ALIGN_LEFT | ALIGN_MIDDLE);
    aboutText.push_back(text);
    append(text);

}

MainWindowGUI::~MainWindowGUI(){
    remove(&bgImageColor);
    remove(&headLine);
    for(u32 i = 0; i < aboutText.size(); ++i){
        remove(aboutText[i]);
        delete aboutText[i];
    }
}
