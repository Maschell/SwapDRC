/****************************************************************************
 * Copyright (C) 2016,2017 Maschell
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
#include "InputGetterMenu.h"
#include "Application.h"
#include "gui/GuiElement.h"
#include "utils/logger.h"
#include "language/gettext.h"
#include "dynamic_libs/padscore_functions.h"

CThread * InputGetterMenu::pThread = NULL;

InputGetterMenu::InputGetterMenu(s32 controller_type)
    : GuiFrame(0,0)
    , backgroundImageData(Resources::GetImageData("InputGetterBG.png"))
    , backgroundImage(backgroundImageData)
    , bgBlur(1280, 720, (GX2Color){0, 0, 0, 255})
    , infoController("", 70, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
    , infoText(gettext("Press any button on the USB-Controller you want to use."), 35, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f))
    , infoTextreturn(gettext("Press B to disable the mapping"), 55, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f))
    , buttonBTrigger(GuiTrigger::CHANNEL_ALL, GuiTrigger::BUTTON_B, true)
    , DPADButtons(0,0)
{
    setControllerType(controller_type);
    CVideo * video = Application::instance()->getVideo();
    width = video->getTvWidth();
    height = video->getTvHeight();
    gameLauncherMenuFrame = GuiFrame(width, height);
    std::string name;

    infoController.setText(name.c_str());
    infoController.setAlignment(ALIGN_TOP|ALIGN_CENTER);
    infoController.setPosition(0,-155);
    infoText.setPosition(0,0);
    infoTextreturn.setPosition(0,-245);
    //infoTextreturn.setScale(2.0f);
    gameLauncherMenuFrame.append(&infoController);
    gameLauncherMenuFrame.append(&infoText);
    gameLauncherMenuFrame.append(&infoTextreturn);

    bgBlur.setAlpha(0.6f);
    append(&bgBlur);

    append(&backgroundImage);

    DPADButtons.setTrigger(&buttonBTrigger);

    DPADButtons.clicked.connect(this, &InputGetterMenu::OnDPADClick);
    gameLauncherMenuFrame.append(&DPADButtons);

    gameLauncherMenuFrame.append(&infoText);

    append(&gameLauncherMenuFrame);
    InputGetterMenu::GetInputsAsync(this);
}

InputGetterMenu::~InputGetterMenu(){
    Resources::RemoveImageData(backgroundImageData);
    //log_printf("Existing InputGetterMenu\n");
    if(InputGetterMenu::pThread != NULL){
        exitInputThread = 1;
        DCFlushRange((void*)&exitInputThread,sizeof(exitInputThread));
        //log_printf("exitInputThread = 1\n");
        delete InputGetterMenu::pThread;
        //log_printf("delete InputGetterMenu::pThread; done\n");
        InputGetterMenu::pThread = NULL;
    }
}

void InputGetterMenu::GetInputsAsync(InputGetterMenu * menu)
{
    InputGetterMenu::pThread = CThread::create(InputGetterMenu::GetInputs, (void*)menu, CThread::eAttributeAffCore2 | CThread::eAttributePinnedAff, 29);
    InputGetterMenu::pThread->resumeThread();
}


void InputGetterMenu::GetInputs(CThread *thread, void *arg){
    InputGetterMenu * args = (InputGetterMenu * )arg;
/**/


    if(!args->exitInputThread) args->OnQuitButtonClick(NULL,NULL,NULL);
}

void InputGetterMenu::OnDPADClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger){
	if(trigger == &buttonBTrigger){
	    if(pThread != NULL){
            exitInputThread = 1;
            delete InputGetterMenu::pThread;
            InputGetterMenu::pThread = NULL;
        }
        this->total_result = 1;
		OnQuitButtonClick(button,controller,trigger);
	}
}

s32 InputGetterMenu::getControllerType(){
    return this->controller_type;
}

void InputGetterMenu::setControllerType(s32 controller_type){
    this->controller_type = controller_type;
}

void InputGetterMenu::draw(CVideo *v)
{
    GuiFrame::draw(v);
}

void InputGetterMenu::update(GuiController *c)
{
    GuiFrame::update(c);
}
