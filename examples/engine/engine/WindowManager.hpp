/*
    Libaroma Engine - Window manager
    Copyright (C) <2021> František Kysela <bythedroid@gmail.com>
    
    This file is part of Libaroma Engine
    
    Libaroma Engine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    Libaroma Engine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with Libaroma Engine.  If not, see <http://www.gnu.org/licenses/>.
    
*/

#ifndef _LIBAROMAENGINE_WINDOWMANAGER_HPP_
#define _LIBAROMAENGINE_WINDOWMANAGER_HPP_

#include "aroma.h"

namespace Libaroma {
namespace Engine {

enum listitem_type {
	ITEM,
	CHECKBOX,
	IMAGE
	CAPTION,
	DIV,
	TEXT,
	OPTION
};

class WindowMenuElement {
public:
   WindowMenuElement();
   virtual ~WindowMenuElement();

private:
enum list_item_type;
int id;
std::string text;
std::string variable;
std::string settings_value; 
LIBAROMA_CANVASP ico;
std::string extra;
}; // WindowMenuElement


class Window {
public:
   Window();
   virtual ~Window();

    
private:
int menu_item_id;
std::vector<WindowMenuElement> menu_items;
word menuflags;
word checkflags;
LIBAROMA_WINDOWP win;
LIBAROMA_CONTROLP bar;
LIBAROMA_CONTROLP menu_list;
Window *onClickWindow;
}; // class WindowManager

} // namespace Engine
} // namespace Pterodon

#endif  // _LIBAROMAENGINE_WINDOWMANAGER_HPP_
