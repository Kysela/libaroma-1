#include "aroma.h"
#include "drawer.hpp"

void Pterodon::Drawer::DrawAppbar(
  const char * text,
  word bgcolor,
  word textcolor,
  int y,
  int h,
  byte flags
){
  LIBAROMA_CANVASP dc = libaroma_fb()->canvas;
  /* draw appbar */
  libaroma_draw_rect(
    dc, 0, y, dc->w, h, bgcolor, 0xff
  );
  int txt_x = libaroma_dp(16);
  
  if ((flags&APPBAR_FLAG_ICON_BACK)||(flags&APPBAR_FLAG_ICON_DRAWER)){
    if (flags&APPBAR_FLAG_ICON_BACK){
      libaroma_art_arrowdrawer(
        dc,1,0,
        txt_x,
        y+libaroma_dp(16),
        libaroma_dp(24),
        textcolor,
        0xff, 0, 0.5
      );
    }
    else{
      libaroma_art_arrowdrawer(
        dc,1,1,
        txt_x,
        y+libaroma_dp(16),
        libaroma_dp(24),
        textcolor,
        0xff, 0, 0.5
      );
    }
    txt_x = libaroma_dp((flags&APPBAR_FLAG_WIDEGAP)?72:60);
      
    if (flags&APPBAR_FLAG_SELECTED){
      int sel_w=txt_x+libaroma_dp(16);
      LIBAROMA_CANVASP carea=libaroma_canvas_area(dc,0,y,sel_w,h);
      if (carea){
        int center_xy=(h>>1);
        libaroma_draw_circle(
          carea, textcolor, center_xy-libaroma_dp(16), center_xy, sel_w+libaroma_dp(20), 0x40
        );
        libaroma_canvas_free(carea);
      }
    }
  }
  
  LIBAROMA_TEXT txt = libaroma_text(
    text,
    textcolor,
    dc->w-txt_x,
    LIBAROMA_FONT(0,6)|
    LIBAROMA_TEXT_SINGLELINE|
    LIBAROMA_TEXT_LEFT|
    LIBAROMA_TEXT_BOLD|
    LIBAROMA_TEXT_FIXED_INDENT|
    LIBAROMA_TEXT_FIXED_COLOR|
    LIBAROMA_TEXT_NOHR,
    100
  );
  if (txt){
    int txty=y + ((h>>1)-((libaroma_text_height(txt)>>1))-libaroma_dp(2));
    libaroma_text_draw(
      dc, txt, txt_x, txty
    );
    libaroma_text_free(txt);
  }
  libaroma_sync();
}


void Pterodon::Drawer::ButtonDraw(const char* text, int x, int y, int w, int h) {
  word colorAccent = RGB(ff8800);
  LIBAROMA_CANVASP dc = libaroma_fb()->canvas;
  /* draw text */
  LIBAROMA_TEXT textp = libaroma_text(
    text,
    colorAccent,
    w - libaroma_dp(16),
    LIBAROMA_FONT(1,4)|
    LIBAROMA_TEXT_SINGLELINE|
    LIBAROMA_TEXT_CENTER|
    LIBAROMA_TEXT_FIXED_INDENT|
    LIBAROMA_TEXT_FIXED_COLOR|
    LIBAROMA_TEXT_NOHR,
    100
  );
  int ty = y + (h>>1) - ((libaroma_text_height(textp)>>1));
  libaroma_text_draw(dc,textp,x + libaroma_dp(8),ty);
  libaroma_text_free(textp);
}

int Pterodon::Drawer::ButtonWidth(const char* text) {
  /* draw text */
  LIBAROMA_CANVASP dc = libaroma_fb()->canvas;
  LIBAROMA_TEXT textp = libaroma_text(
    text,
    0,
    dc->w,
    LIBAROMA_FONT(1,4)|
    LIBAROMA_TEXT_SINGLELINE|
    LIBAROMA_TEXT_CENTER|
    LIBAROMA_TEXT_FIXED_INDENT|
    LIBAROMA_TEXT_FIXED_COLOR|
    LIBAROMA_TEXT_NOHR,
    100
  );
  int w = libaroma_dp(8) + libaroma_text_width(textp) + libaroma_dp(8);
  libaroma_text_free(textp);
  return w;
}

void Pterodon::Drawer::DrawDialog(
  const char* Title,
  const char* Message,
  const char* Button1,
  const char* Button2
){
  LIBAROMA_CANVASP dc = libaroma_fb()->canvas;
  int Selection = 0;
  int MaxSelection = (Button1?1:0) + (Button2?1:0);
  
  /* COLORS */
  word colorTextSecondary = RGB(cccccc);
  word colorTextPrimary = RGB(ffffff);
  word colorBackground = RGB(444444);
  word colorSelection = RGB(aaaaaa);
  
  /* Mask Dark */
  libaroma_draw_rect(
    dc, 0, 0, dc->w, dc->h, RGB(000000), 0x7a
  );
  
  /* Init Message & Title Text */
  int dialog_w = dc->w-libaroma_dp(48);
  LIBAROMA_TEXT messagetextp = libaroma_text(
    Message,
    colorTextSecondary,
    dialog_w-libaroma_dp(48),
    LIBAROMA_FONT(0,4)|
    LIBAROMA_TEXT_LEFT|
    LIBAROMA_TEXT_FIXED_INDENT|
    LIBAROMA_TEXT_FIXED_COLOR|
    LIBAROMA_TEXT_NOHR,
    100
  );
  LIBAROMA_TEXT textp = libaroma_text(
    Title,
    colorTextPrimary,
    dialog_w-libaroma_dp(48),
    LIBAROMA_FONT(1,6)|
    LIBAROMA_TEXT_LEFT|
    LIBAROMA_TEXT_FIXED_INDENT|
    LIBAROMA_TEXT_FIXED_COLOR|
    LIBAROMA_TEXT_NOHR,
    100
  );

  int dialog_h =
    libaroma_dp(120)+
    libaroma_text_height(textp)+
    libaroma_text_height(messagetextp);
  int dialog_x = libaroma_dp(24);
  int dialog_y = (dc->h>>1)-(dialog_h>>1);
  
  /* draw fake shadow */
  int z;
  int shadow_sz=libaroma_dp(2);
  byte shadow_opa = (byte) (0x60 / shadow_sz);
  for (z=1;z<shadow_sz;z++){
    int wp=z*2;
    libaroma_gradient_ex(dc,
      dialog_x-z, dialog_y+(z>>1),
      dialog_w+wp, dialog_h+wp,
      0,0,
      libaroma_dp(4), 
      0x1111,
      shadow_opa, shadow_opa
    );
  }
  
  /* draw dialog */
  libaroma_gradient(dc,
    dialog_x, dialog_y,
    dialog_w, dialog_h,
    colorBackground,colorBackground,
    libaroma_dp(4), /* rounded 4dp */
    0x1111 /* all corners */
  );
  
  /* draw texts */
  libaroma_text_draw(
    dc,
    textp,
    dialog_x+libaroma_dp(24),
    dialog_y+libaroma_dp(24)
  );
  libaroma_text_free(textp);

  /* draw text */
  libaroma_text_draw(
    dc,
    messagetextp,
    dialog_x+libaroma_dp(24),
    dialog_y+libaroma_dp(24)+libaroma_text_height(textp) + libaroma_dp(20)
  );
  libaroma_text_free(messagetextp);
  
  
  int i; /* i is selection */
  for (i=0;i<2;i++){
    Selection=i;
    int button_y = dialog_y+dialog_h-libaroma_dp(52);
    
    /* clean button area */
    libaroma_draw_rect(dc, dialog_x, button_y, dialog_w, libaroma_dp(36), colorBackground, 0xff);
      
    if(Button1) {
      /* button1 */
      int button_w = ButtonWidth(Button1);
      int button_x = dialog_x+dialog_w-button_w-libaroma_dp(16);
      
      if(Selection==0) {
        libaroma_gradient_ex(dc,
          button_x,button_y,
          button_w, libaroma_dp(36),
          colorSelection,colorSelection,
          libaroma_dp(2), /* rounded 2dp */
          0x1111, /* all corners */
          0x40, 0x40 /* start & end alpha */
        );
      }
      ButtonDraw(Button1, button_x, button_y-libaroma_dp(2), button_w, libaroma_dp(36));
  
      /* button2 */
      if(Button2) {
        button_w = ButtonWidth(Button2);
        button_x -= (libaroma_dp(8)+button_w);
        if(Selection==1) {
          libaroma_gradient_ex(dc,
            button_x,button_y,
            button_w, libaroma_dp(36),
            colorSelection,colorSelection,
            libaroma_dp(2), /* rounded 2dp */
            0x1111, /* all corners */
            0x40, 0x40 /* start & end alpha */
          );
        }
        ButtonDraw(Button2, button_x, button_y-libaroma_dp(2), button_w, libaroma_dp(36));
      }
    }
    libaroma_sync();
  }
}


