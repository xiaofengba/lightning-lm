/*
 * @Author: nuc 1078456645@qq.com
 * @Date: 2025-11-17 10:41:09
 * @LastEditors: nuc 1078456645@qq.com
 * @LastEditTime: 2025-11-26 11:27:51
 * @FilePath: /lightning-lm_ws/src/lightning-lm/src/app/run_loc_online.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
//
// Created by xiang on 25-3-18.
//

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "core/system/loc_system.h"
#include "ui/pangolin_window.h"
#include "wrapper/ros_utils.h"

DEFINE_string(config, "./config/default.yaml", "配置文件");

/// 运行定位的测试
int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_colorlogtostderr = true;
    FLAGS_stderrthreshold = google::INFO;

    google::ParseCommandLineFlags(&argc, &argv, true);
    using namespace lightning;

    rclcpp::init(argc, argv);

    LocSystem::Options opt;
    LocSystem loc(opt);

    if (!loc.Init(FLAGS_config)) {
        LOG(ERROR) << "failed to init loc";
    }

    Eigen::Vector3d t_initial(0.0, -1.5, 0.0);

    /// 默认起点开始定位
    // loc.SetInitPose(SE3::trans(t_initial));
    loc.SetInitPose(SE3());
    loc.Spin();

    rclcpp::shutdown();

    return 0;
}