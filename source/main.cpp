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

#include "gui\guimain.h"
#include "utils\dataformat.h"
#include "engine\particleeditor.h"
#include "iostream"

using namespace std;



//BUG: Editor returns -1 if it doesn't find the map file, check the loadMap() function

BITMAP *buffer;

GuiResources resources;
InputMouse mouse;
GuiMain gui;
ParticleEditor editor;
DataFormat convert;

volatile int peditor_exit = FALSE;
volatile int main_timer;

void inc_main_timer(void) {
    main_timer++;
}
END_OF_FUNCTION(inc_main_timer)

void close_button_handler(void) {
    peditor_exit = TRUE;

}
END_OF_FUNCTION(close_button_handler)

int main(void) {

    allegro_init();
    install_keyboard();
    install_timer();
    install_mouse();

    set_color_depth(32);
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1024, 768,0,0)!=0)
        return 1;

    set_window_title("Particle Editor v0.1");

    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);

    LOCK_VARIABLE(main_timer);
    LOCK_FUNCTION(inc_main_timer);
    install_int_ex(inc_main_timer, BPS_TO_TIMER(120));

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(buffer, makecol(0, 0, 0));

    resources.loadResources();
    mouse.initMouse();
    gui.loadInterface();
    editor.initEditor();

    mouse.setCursor(CURSOR);

    while (!peditor_exit) {

        //show_mouse(buffer);
        while (main_timer == 0) {
            rest(100 / 100);
        }
        while (main_timer > 0) {
            int old_timer = main_timer;

            if (key[KEY_ESC]) peditor_exit = TRUE;

            gui.updateInterface();
            editor.editorEngine();

            editor.renderEditor(buffer);
            gui.drawInterface(buffer);

            mouse.draw(buffer);

            acquire_screen();
            masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            release_screen();

            clear_to_color(buffer, makecol(0, 0, 0));

            main_timer--;

            if (old_timer <= main_timer)
                break;
        }
    }

    mouse.freeMouse();
    resources.freeResources();
    editor.freeEditor();

    destroy_bitmap(buffer);
    return 0;
}
END_OF_MAIN()
