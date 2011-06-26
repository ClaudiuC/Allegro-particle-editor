///////////////////////////////////////////////////////////////////////////////
//            Copyright (C) 2009 by Hazardous Gaming
//                         All Rights Reserved
//
// This code is licensed under the MIT License. It is free software
// and you may modify it and/or redistribute it under the terms of this license.
// See http://www.opensource.org/licenses/mit-license.php for details.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////

#include "guimain.h"

extern InputMouse mouse;
extern DataFormat convert;
extern ParticleEditor editor;

GuiMain::GuiMain() {
    panelState = STATE_PARTICLE_EDIT;

    grid = quit = false;
    gridDensity = 24;

    brush = BRUSH_NONE;

    mouse_frame = FRAME_WORKSPACE;
    gui_x = gui_y = 0;

    preview = false;

    emptyParticleStruct();
}

GuiMain::~GuiMain() {
    //dtor
}

void GuiMain::loadInterface() {
    frame.addFrame(0, 0, SCREEN_W, SCREEN_H, "Particle editor v0.1");
    frame.addFrame(768, 16, 256, SCREEN_H, "Property pallette");
    frameSidebar = frame.getLastFrameID();
    frame.addFrame(0, 16, 768, SCREEN_H, "Workspace");
    frameMain = frame.getLastFrameID();

    button.addButton(778, 45, "Particles");
    buttonParticles = button.getLastButtonID();
    button.addButton(778, 65, "Forces   ");
    buttonForces = button.getLastButtonID();

    button.addButton(button.getButtonSizeW(buttonParticles)+788, 45, "Place element");
    buttonPlaceElement = button.getLastButtonID();
    button.addButton(button.getButtonSizeW(buttonForces)+788, 65, "Simulate     ");
    buttonPreview = button.getLastButtonID();

    //! Particle settings
    // DX
    field.addField(788+text_length(font, "X dir"), 140, text_length(font, "XXX")+20, text_height(font), "X dir ");
    fieldSettings[PARTICLE_DX] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[PARTICLE_DX])+field.getFieldPosX(fieldSettings[PARTICLE_DX])+20 , 140, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[PARTICLE_DX_RAND] = field.getLastFieldID();

    // DY
    field.addField(788+text_length(font, "Y dir"), 165, text_length(font, "XXX")+20, text_height(font), "Y dir ");
    fieldSettings[PARTICLE_DY] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[PARTICLE_DY])+field.getFieldPosX(fieldSettings[PARTICLE_DY])+20 , 165, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[PARTICLE_DY_RAND] = field.getLastFieldID();

    // RX
    field.addField(788+text_length(font, "RandX"), 190, text_length(font, "XXX")+20, text_height(font), "Rand X");
    fieldSettings[PARTICLE_RX] = field.getLastFieldID();

    // RY
    field.addField(788+text_length(font, "RandY"), 215, text_length(font, "XXX")+20, text_height(font), "Rand Y");
    fieldSettings[PARTICLE_RY] = field.getLastFieldID();

    //LIFE
    field.addField(788+text_length(font, "Life "), 240, text_length(font, "XXX")+20, text_height(font), "Life  ");
    fieldSettings[PARTICLE_LIFE] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[PARTICLE_LIFE])+field.getFieldPosX(fieldSettings[PARTICLE_LIFE])+20 , 240, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[PARTICLE_LIFE_RAND] = field.getLastFieldID();

    // SPEED
    field.addField(788+text_length(font, "Speed"), 265, text_length(font, "XXX")+20, text_height(font), "Speed ");
    fieldSettings[PARTICLE_SPEED] = field.getLastFieldID();

    // COLOR R
    field.addField(788+text_length(font, "Red  "), 290, text_length(font, "XXX")+20, text_height(font), "Red   ");
    fieldSettings[PARTICLE_COL_R] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[PARTICLE_COL_R])+field.getFieldPosX(fieldSettings[PARTICLE_COL_R])+20 , 290, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[PARTICLE_COL_R_RAND] = field.getLastFieldID();

    // COLOR G
    field.addField(788+text_length(font, "Green"), 315, text_length(font, "XXX")+20, text_height(font), "Green ");
    fieldSettings[PARTICLE_COL_G] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[PARTICLE_COL_G])+field.getFieldPosX(fieldSettings[PARTICLE_COL_G])+20 , 315, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[PARTICLE_COL_G_RAND] = field.getLastFieldID();

    // COLOR B
    field.addField(788+text_length(font, "Blue "), 340, text_length(font, "XXX")+20, text_height(font), "Blue  ");
    fieldSettings[PARTICLE_COL_B] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[PARTICLE_COL_B])+field.getFieldPosX(fieldSettings[PARTICLE_COL_B])+20 , 340, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[PARTICLE_COL_B_RAND] = field.getLastFieldID();

    //! Force settings
    // DX
    field.addField(788+text_length(font, "X dir"), 140, text_length(font, "XXX")+20, text_height(font), "X dir ");
    fieldSettings[FORCE_DX] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[FORCE_DX])+field.getFieldPosX(fieldSettings[FORCE_DX])+20 , 140, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[FORCE_DX_RAND] = field.getLastFieldID();

    // DY
    field.addField(788+text_length(font, "Y dir"), 165, text_length(font, "XXX")+20, text_height(font), "X dir ");
    fieldSettings[FORCE_DY] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[FORCE_DY])+field.getFieldPosX(fieldSettings[FORCE_DY])+20 , 165, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[FORCE_DY_RAND] = field.getLastFieldID();

    // RX
    field.addField(788+text_length(font, "RandX"), 190, text_length(font, "XXX")+20, text_height(font), "Rand X");
    fieldSettings[FORCE_RX] = field.getLastFieldID();

    // RY
    field.addField(788+text_length(font, "RandY"), 215, text_length(font, "XXX")+20, text_height(font), "Rand Y");
    fieldSettings[FORCE_RY] = field.getLastFieldID();

    //LIFE
    field.addField(788+text_length(font, "Life "), 240, text_length(font, "XXX")+20, text_height(font), "Life  ");
    fieldSettings[FORCE_LIFE] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[FORCE_LIFE])+field.getFieldPosX(fieldSettings[FORCE_LIFE])+20 , 240, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[FORCE_LIFE_RAND] = field.getLastFieldID();

    // SPEED
    field.addField(788+text_length(font, "Speed"), 265, text_length(font, "XXX")+20, text_height(font), "Speed ");
    fieldSettings[FORCE_SPEED] = field.getLastFieldID();

    // COLOR R
    field.addField(788+text_length(font, "Red  "), 290, text_length(font, "XXX")+20, text_height(font), "Red   ");
    fieldSettings[FORCE_COL_R] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[FORCE_COL_R])+field.getFieldPosX(fieldSettings[FORCE_COL_R])+20 , 290, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[FORCE_COL_R_RAND] = field.getLastFieldID();

    // COLOR G
    field.addField(788+text_length(font, "Green"), 315, text_length(font, "XXX")+20, text_height(font), "Green ");
    fieldSettings[FORCE_COL_G] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[FORCE_COL_G])+field.getFieldPosX(fieldSettings[FORCE_COL_G])+20 , 315, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[FORCE_COL_G_RAND] = field.getLastFieldID();

    // COLOR B
    field.addField(788+text_length(font, "Blue "), 340, text_length(font, "XXX")+20, text_height(font), "Blue  ");
    fieldSettings[FORCE_COL_B] = field.getLastFieldID();

    field.addField(field.getFieldSizeW(fieldSettings[FORCE_COL_B])+field.getFieldPosX(fieldSettings[FORCE_COL_B])+20 , 340, text_length(font, "XXX")+20, text_height(font), " ");
    fieldSettings[FORCE_COL_B_RAND] = field.getLastFieldID();

    field.setAllFieldDefault("0");
    /*
    label.addLabel(770, 370, makecol(180,180,180), "X direction: 0");
    statsLabels[P_DX_LABEL] = label.getLastLabelID();

    label.addLabel(770, 390, makecol(180,180,180), "Randomness: 0");
    statsLabels[P_DX_RAND_LABEL] = label.getLastLabelID();

    label.addLabel(770, 415, makecol(180,180,180), "Y direction: 0");
    statsLabels[P_DY_LABEL] = label.getLastLabelID();

    label.addLabel(770, 435, makecol(180,180,180), "Randomness: 0");
    statsLabels[P_DY_RAND_LABEL] = label.getLastLabelID();

    label.addLabel(770, 460, makecol(180,180,180), "X position randomness: 0");
    statsLabels[P_RX_LABEL] = label.getLastLabelID();

    label.addLabel(770, 480, makecol(180,180,180), "Y position randomness: 0");
    statsLabels[P_RY_LABEL] = label.getLastLabelID();

    label.addLabel(770, 505, makecol(180,180,180), "Life: 0");
    statsLabels[P_LIFE_LABEL] = label.getLastLabelID();

    label.addLabel(770, 525, makecol(180,180,180), "Randomness: 0");
    statsLabels[P_LIFE_RAND_LABEL] = label.getLastLabelID();

    label.addLabel(770, 550, makecol(180,180,180), "Speed: 0");
    statsLabels[P_SPEED_LABEL] = label.getLastLabelID();

    label.addLabel(770, 575, makecol(180,180,180), "Red: 0");
    statsLabels[P_RED_LABEL] = label.getLastLabelID();

    label.addLabel(770, 595, makecol(180,180,180), "Randomness: 0");
    statsLabels[P_RED_RAND_LABEL] = label.getLastLabelID();

    label.addLabel(770, 620, makecol(180,180,180), "Green: 0");
    statsLabels[P_GREEN_LABEL] = label.getLastLabelID();

    label.addLabel(770, 640, makecol(180,180,180), "Randomness: 0");
    statsLabels[P_GREEN_RAND_LABEL] = label.getLastLabelID();

    label.addLabel(770, 665, makecol(180,180,180), "Blue: 0");
    statsLabels[P_BLUE_LABEL] = label.getLastLabelID();

    label.addLabel(770, 685, makecol(180,180,180), "Randomness: 0");
    statsLabels[P_BLUE_RAND_LABEL] = label.getLastLabelID();
    */

    //field.addField(788 + text_length(font, "Save as"), 385, text_length(font, "particle.dat")+20, text_height(font), "Save as ");
    fieldSave = field.getLastFieldID();
    //button.addButton(788 + field.getFieldSizeW(fieldSave) + 70, 380, " OK ");
    buttonSave = button.getLastButtonID();

    //field.addField(788 + text_length(font, "Load   "), 410, text_length(font, "particle.dat")+20, text_height(font), "Load    ");
    fieldLoad = field.getLastFieldID();
    //button.addButton(788 + field.getFieldSizeW(fieldSave) + 70, 405, " OK ");
    buttonLoad = button.getLastButtonID();

    //field.addField(788 + text_length(font, "Create "), 435, text_length(font, "particle.dat")+20, text_height(font), "Create  ");
    fieldCreate = field.getLastFieldID();
    //button.addButton(788 + field.getFieldSizeW(fieldSave) + 70, 430, " OK ");
    buttonCreate = button.getLastButtonID();
}

void GuiMain::updateInterface() {

    field.hideAllFields();
    button.hideButton(buttonForces);
    button.hideButton(buttonPreview);
    //field.showField(fieldSave);
    //field.showField(fieldLoad);
    //field.showField(fieldCreate);

    switch (panelState) {
    case STATE_PARTICLE_EDIT: {
        for (short field_id = PARTICLE_DX; field_id < FORCE_DX; field_id++) {
            field.showField(field_id);
        }
        break;

    }
    case STATE_FORCE_EDIT: {
        for (short field_id = FORCE_DX; field_id <= FORCE_COL_B_RAND; field_id++) {
            field.showField(field_id);
        }
        break;

    }
    case STATE_SIMULATE: {
        //field.hideAllFields();
        for (short field_id = PARTICLE_DX; field_id <= FORCE_COL_B_RAND; field_id++) {
            field.hideField(field_id);
        }
        break;
    }
    }

    field.updateFields();

    short button_pressed = -1;
    if (button_pressed == -1) button_pressed = button.updateButtons();

    if (button_pressed != -1) {
        if (button_pressed == buttonParticles) {
            panelState = STATE_PARTICLE_EDIT;
            brush = BRUSH_NONE;
        }
        if (button_pressed == buttonForces) {
            //panelState = STATE_FORCE_EDIT;
            //brush = BRUSH_NONE;
        }
        if (button_pressed == buttonPlaceElement) {
            switch (panelState) {
            case STATE_PARTICLE_EDIT: {
                brush = BRUSH_PARTICLE;
                //fillParticleStruct();

                break;
            }
            case STATE_FORCE_EDIT: {
                //brush = BRUSH_FORCE;
                //emptyParticleStruct();
                break;
            }
            case STATE_SIMULATE: {
                //brush = BRUSH_NONE;
                //panelState = STATE_PARTICLE_EDIT;
                break;
            }
            }
        }
        if (button_pressed == buttonPreview) {
            //panelState = STATE_SIMULATE;
            //brush = BRUSH_NONE;
        }
    }

    switch (panelState) {
    case STATE_PARTICLE_EDIT: {
        frame.setFrameLabel(frameSidebar, "Particle properties");
        frame.setFrameLabel(frameMain, "Particle mode");
        button.setButtonActive(buttonParticles);
        button.setButtonLabel(buttonPlaceElement, "Place emitter");
        if (brush == BRUSH_PARTICLE) {
            button.setButtonActive(buttonPlaceElement);
        }

        //button.setButtonActive(buttonPlaceElement);
        break;
    }
    case STATE_FORCE_EDIT: {
        frame.setFrameLabel(frameSidebar, "Force properties");
        frame.setFrameLabel(frameMain, "Force mode");
        button.setButtonActive(buttonForces);
        button.setButtonLabel(buttonPlaceElement, "Place force");
        //button.setButtonActive(buttonPlaceElement);
        if (brush == BRUSH_FORCE) {
            button.setButtonActive(buttonPlaceElement);
        }
        break;
    }
    case STATE_SIMULATE: {
        frame.setFrameLabel(frameMain, "Simulation");
        button.setButtonActive(buttonPreview);

        break;
    }
    }

    if (mouse_x < 768-gridDensity-8 && mouse_y > gridDensity &&
            mouse_x > gridDensity && mouse_y < SCREEN_H) {
        mouse.setCursor(NONE);
        gui_x = (mouse_x/gridDensity)*gridDensity+(mouse_x/gridDensity);
        gui_y = (mouse_y/gridDensity)*gridDensity;
        mouse_frame = FRAME_WORKSPACE;
    } else {
        mouse.setCursor(CURSOR);
        gui_x = -1;
        gui_y = -1;
        mouse_frame = FRAME_SIDEBAR;
    }

    /*
    if (key[KEY_UP]) {
        if (gridDensity < 257) {
            gridDensity+=8;
            editor.resetEmitter();
        }
    }

    if (key[KEY_DOWN]) {
        if (gridDensity > 24) {
            gridDensity-=8;
            editor.resetEmitter();
        }
    }
    */
    //label.setLabelText(statsLabels[P_DX_LABEL], dx);
}

void GuiMain::drawInterface(BITMAP *bmp) {
    frame.drawHorizontalSeparator(bmp, 768, SCREEN_W, 100);
    frame.drawHorizontalSeparator(bmp, 768, SCREEN_W, 360);

    frame.drawFrames(bmp);

    button.drawButtons(bmp);
    field.drawFields(bmp);
    label.drawLabels(bmp);
}

RAND_VALUE GuiMain::fillValue(string constant, string rand) {
    RAND_VALUE returnValue;

    returnValue.constant = convert.stod(constant);
    returnValue.rand = convert.stod(rand);

    return returnValue;
}

void GuiMain::fillParticleStruct() {
    particleSettings.dx = fillValue(field.getFieldText(PARTICLE_DX), field.getFieldText(PARTICLE_DX_RAND));
    if (convert.stod(field.getFieldText(PARTICLE_DX)) == 0) field.setFieldText(PARTICLE_DX, "0");
    if (convert.stod(field.getFieldText(PARTICLE_DX_RAND)) == 0) field.setFieldText(PARTICLE_DX_RAND, "0");

    particleSettings.dy = fillValue(field.getFieldText(PARTICLE_DY), field.getFieldText(PARTICLE_DY_RAND));
    if (convert.stod(field.getFieldText(PARTICLE_DY)) == 0) field.setFieldText(PARTICLE_DY, "0");
    if (convert.stod(field.getFieldText(PARTICLE_DY_RAND)) == 0) field.setFieldText(PARTICLE_DY_RAND, "0");

    particleSettings.rx = convert.stod(field.getFieldText(PARTICLE_RX));
    particleSettings.ry = convert.stod(field.getFieldText(PARTICLE_RY));
    if (convert.stoi(field.getFieldText(PARTICLE_RX)) == 0) field.setFieldText(PARTICLE_RX, "0");
    if (convert.stod(field.getFieldText(PARTICLE_RY)) == 0) field.setFieldText(PARTICLE_RY, "0");

    particleSettings.life = fillValue(field.getFieldText(PARTICLE_LIFE), field.getFieldText(PARTICLE_LIFE_RAND));
    if (convert.stod(field.getFieldText(PARTICLE_LIFE)) == 0) field.setFieldText(PARTICLE_LIFE, "0");
    if (convert.stod(field.getFieldText(PARTICLE_LIFE_RAND)) == 0) field.setFieldText(PARTICLE_LIFE_RAND, "0");

    particleSettings.speed = convert.stod(field.getFieldText(PARTICLE_SPEED));
    if (convert.stod(field.getFieldText(PARTICLE_SPEED)) == 0) field.setFieldText(PARTICLE_SPEED, "0");

    particleSettings.r = fillValue(field.getFieldText(PARTICLE_COL_R), field.getFieldText(PARTICLE_COL_R_RAND));
    if (convert.stoi(field.getFieldText(PARTICLE_COL_R)) == 0) field.setFieldText(PARTICLE_COL_R, "0");
    if (convert.stoi(field.getFieldText(PARTICLE_COL_R_RAND)) == 0) field.setFieldText(PARTICLE_COL_R_RAND, "0");

    particleSettings.g = fillValue(field.getFieldText(PARTICLE_COL_G), field.getFieldText(PARTICLE_COL_G_RAND));
    if (convert.stoi(field.getFieldText(PARTICLE_COL_G)) == 0) field.setFieldText(PARTICLE_COL_G, "0");
    if (convert.stoi(field.getFieldText(PARTICLE_COL_G_RAND)) == 0) field.setFieldText(PARTICLE_COL_G_RAND, "0");

    particleSettings.b = fillValue(field.getFieldText(PARTICLE_COL_B), field.getFieldText(PARTICLE_COL_B_RAND));
    if (convert.stoi(field.getFieldText(PARTICLE_COL_B)) == 0) field.setFieldText(PARTICLE_COL_B, "0");
    if (convert.stod(field.getFieldText(PARTICLE_COL_B_RAND)) == 0) field.setFieldText(PARTICLE_COL_B_RAND, "0");
}

void GuiMain::emptyParticleStruct() {
    particleSettings.dx = fillValue("0","0");
    particleSettings.dy = fillValue("0","0");

    particleSettings.rx = 0;
    particleSettings.ry = 0;

    particleSettings.life = fillValue("0","0");
    particleSettings.speed = 0;

    particleSettings.r = fillValue("0","0");
    particleSettings.g = fillValue("0","0");
    particleSettings.b = fillValue("0","0");
}

PARTICLE_SETTINGS GuiMain::returnEmptyParticle() {
    PARTICLE_SETTINGS returnValue;

    returnValue.dx = fillValue("0","0");
    returnValue.dy = fillValue("0","0");

    returnValue.rx = 0;
    returnValue.ry = 0;

    returnValue.life = fillValue("0","0");
    returnValue.speed = 0;

    returnValue.r = fillValue("0","0");
    returnValue.g = fillValue("0","0");
    returnValue.b = fillValue("0","0");

    return returnValue;
}
