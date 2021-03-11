/*
    Pterodon Recovery - bootup manager
    Copyright (C) <2019> ATGDroid <bythedroid@gmail.com>
    
    This file is part of Pterodon Recovery Project
    
    Pterodon Recovery is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    Pterodon Recovery is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with Pterodon Recovery.  If not, see <http://www.gnu.org/licenses/>.
    
*/

#ifndef PTERODON_BOOT_HPP
#define PTERODON_BOOT_HPP

#include "aroma.h"
#include <string>
#include <vector>

namespace Pterodon {
namespace Gui {

class BootManager {
public:
    static void Initialize(void);
    //static void ShowSplash(void);
    static void ShowConsole(void);
    static void ShowSplash(const std::string& splash_image_name);
}; // class BootManager

} // namespace Gui
} // namespace Pterodon

#endif  // PTERODON_BOOT_HPP
