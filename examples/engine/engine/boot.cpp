#include "aroma.h"
#include "minlist.hpp"
#include "drawer.hpp"
#include "boot.hpp"
#include "engine.hpp"
#include "gui.hpp"
#include "pterodon.h"
#include "device_driver.hpp"
#include <string>
#include <vector>

void Pterodon::Gui::BootManager::Initialize(void) {
if (!libaroma_start_basic())
     return;
#ifdef PTERO_FB_BLANK_ON_BOOT  
  libaroma_fb_blank(1);
  libaroma_fb_blank(0);
#endif
  Pterogui()->current_display_brightness = -1;
  Pterodon::DeviceDriver::GetMaxDisplayBrightness(&Pterogui()->max_display_brightness);
  Pterodon::DeviceDriver::SetBrightness(0);
  Pterodon::DeviceDriver::SetBrightness(100);
  Pterodon::Gui::Engine::LoadFont("Roboto-Regular.ttf");
  libaroma_canvas_blank(libaroma_fb()->canvas);
}

void Pterodon::Gui::BootManager::ShowSplash(const std::string& splash_image_name) {
LIBAROMA_CANVASP splash = Pterodon::Gui::Engine::LoadImage(splash_image_name); 
  if (splash){
    libaroma_canvas_blank(libaroma_fb()->canvas);
    libaroma_canvas_fillcolor(splash, RGB(44d036));
    libaroma_draw(libaroma_fb()->canvas,splash,0,0,1);
    libaroma_sync();
    libaroma_canvas_free(splash);
  }
}


void Pterodon::Gui::BootManager::ShowConsole(void) {
	LIBAROMA_CANVASP dc = libaroma_fb()->canvas;
    int i;
    int statusbar_height = libaroma_dp(24);
    int appbar_height    = libaroma_dp(56);
    int list_y           = statusbar_height + appbar_height;
    int list_height      = dc->h-list_y;

  libaroma_draw_rect(
      dc, 0, 0, dc->w, statusbar_height, RGB(335577), 0xff
    );
    libaroma_draw_text(
    	dc,
    	"Pterodon Recovery",
    	0, libaroma_dp(2) ,RGB(ffffff), dc->w,
    	LIBAROMA_FONT(0,3)|LIBAROMA_TEXT_CENTER,
    	100
    );
    /* set appbar */
    Pterodon::Drawer::DrawAppbar(
      "Starting Pterodon",
      RGB(446688),
      RGB(ffffff),
      statusbar_height,
      appbar_height,
      APPBAR_FLAG_ICON_DRAWER|APPBAR_FLAG_SELECTED
    );
    
    /*
     * Create List
     */
     MinList list(
      dc->w,
      libaroma_dp(72),
      RGB(ffffff),
      RGB(cccccc),
      RGB(000000),
      RGB(000000)
    );
    
    /*
     * Add List Items
     */
    for (i=0;i<30;i++){
      char title[64];
      char subtitle[64];
      snprintf(title,64,"Item Number %i", i+1);
      snprintf(subtitle,64,"This is subtitle text number %i", i+1);
      list.add(
        NULL,
        title,
        subtitle,
        0
      );
    }
    
    /* show & change list selection */
    for (i=-1;i<2;i++){
      list.show(i, 0, list_y, list_height);
      libaroma_sleep(300);
    }
        
    /* redraw appbar & list */
    Pterodon::Drawer::DrawAppbar(
      "Boot done",
      RGB(446688),
      RGB(ffffff),
      statusbar_height,
      appbar_height,
      APPBAR_FLAG_ICON_DRAWER|APPBAR_FLAG_SELECTED
    );
    
    /* show & change list selection */
    for (i=-1;i<30;i++){
      list.show(i, 0, list_y, list_height);
      libaroma_sleep(300);
    }
} /* End of main */
