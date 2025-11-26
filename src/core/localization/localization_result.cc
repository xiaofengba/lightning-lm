/*
 * @Author: nuc 1078456645@qq.com
 * @Date: 2025-11-17 10:41:09
 * @LastEditors: nuc 1078456645@qq.com
 * @LastEditTime: 2025-11-26 09:58:00
 * @FilePath: /lightning-lm_ws/src/lightning-lm/src/core/localization/localization_result.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
//
// Created by xiang on 24-4-11.
//

#include "localization_result.h"
#include "core/lightning_math.hpp"

namespace lightning::loc {

geometry_msgs::msg::TransformStamped LocalizationResult::ToGeoMsg(std::string child_frame_id) const {
    geometry_msgs::msg::TransformStamped msg;
    msg.header.frame_id = "map";
    msg.header.stamp = math::FromSec(timestamp_);
    msg.child_frame_id = child_frame_id;

    msg.transform.translation.x = pose_.translation().x();
    msg.transform.translation.y = pose_.translation().y();
    msg.transform.translation.z = pose_.translation().z();

    msg.transform.rotation.x = pose_.so3().unit_quaternion().x();
    msg.transform.rotation.y = pose_.so3().unit_quaternion().y();
    msg.transform.rotation.z = pose_.so3().unit_quaternion().z();
    msg.transform.rotation.w = pose_.so3().unit_quaternion().w();

    return msg;
}

NavState LocalizationResult::ToNavState() const {
    NavState ret;
    ret.timestamp_ = timestamp_;
    ret.confidence_ = confidence_;
    ret.pos_ = pose_.translation();
    ret.rot_ = pose_.so3();
    ret.pose_is_ok_ = status_ == LocalizationStatus::GOOD;

    ret.vel_ = (pose_.so3() * vel_b_);

    return ret;
}

}  // namespace lightning::loc
