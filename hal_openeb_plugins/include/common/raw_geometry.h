/**********************************************************************************************************************
 * Copyright (c) Prophesee S.A.                                                                                       *
 *                                                                                                                    *
 * Licensed under the Apache License, Version 2.0 (the "License");                                                    *
 * you may not use this file except in compliance with the License.                                                   *
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0                                 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed   *
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.                      *
 * See the License for the specific language governing permissions and limitations under the License.                 *
 **********************************************************************************************************************/

#ifndef RAW_GEOMETRY_H
#define RAW_GEOMETRY_H

#include <metavision/hal/facilities/i_geometry.h>

namespace Metavision {

class RawGeometry : public Metavision::I_Geometry {
public:
    RawGeometry(const int width, const int height);

    /// @brief Returns width of the sensor in pixels
    ///
    /// @return Sensor's width
    int get_width() const override final;

    /// @brief Returns height of the sensor in pixels
    ///
    /// @return Sensor's height
    int get_height() const override final;

private:
    int width_;
    int height_;
};

} // namespace Metavision

#endif // RAW_GEOMETRY_H
