#ifndef PTERODON_DRAWER_HPP
#define PTERODON_DRAWER_HPP

#include "aroma.h"

#define APPBAR_FLAG_ICON_BACK   1 /* back arrow */
#define APPBAR_FLAG_ICON_DRAWER 2 /* drawer */
#define APPBAR_FLAG_SELECTED    4 /* selected */
#define APPBAR_FLAG_WIDEGAP     8 /* align text with text in listbox */

namespace Pterodon {

class Drawer {
public:
    static void DrawAppbar(const char* text, word bgcolor, word textcolor, int y, int h, byte flags);
    static void ButtonDraw(const char* text, int x, int y, int w, int h);
    static int ButtonWidth(const char* text);
    static void DrawDialog(const char * Title, const char * Message, const char * Button1, const char * Button2);
}; // class BootManager

}

#endif // PTERODON_DRAWER_HPP
