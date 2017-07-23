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
#ifndef _MAIN_WINDOW_GUI_H_
#define _MAIN_WINDOW_GUI_H_

#include <vector>
#include <vector>
#include <queue>
#include "gui/Gui.h"

class CVideo;

class MainWindowGUI : public GuiFrame{
public:
    MainWindowGUI(s32 w, s32 h);
    virtual ~MainWindowGUI();
private:
    s32 width, height;
    GuiImage bgImageColor;
    GuiText headLine;
    std::vector<GuiText *> aboutText;
};

#endif //_MAIN_WINDOW_GUI_H_
