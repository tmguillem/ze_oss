#!/usr/bin/env bash

# cuda
rm imp_3rdparty_cuda_toolkit/CATKIN_IGNORE
rm imp_cu_core/CATKIN_IGNORE
rm imp_cu_correspondence/CATKIN_IGNORE
rm imp_cu_imgproc/CATKIN_IGNORE
rm imp_benchmark_aligned_allocator/CATKIN_IGNORE
rm imp_ros_rof_denoising/CATKIN_IGNORE
rm imp_app_pangolin_example/CATKIN_IGNORE

# rely on cuda dependent packages
rm imp_tools_cmd/CATKIN_IGNORE

# rely on specific messages
rm ze_data_provider/CATKIN_IGNORE

# misc
rm ze_pangolin/CATKIN_IGNORE
rm imp_bridge_pangolin/CATKIN_IGNORE
