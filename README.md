# ze_oss
If you do not have CUDA installed, simply run the script `ignore_cuda.bash` and it will put a `CATKIN_IGNORE` in each CUDA related packages. The script `enable_cuda.bash` will do the opposite.

You might also need to ignore the package `ze_data_provider` since it relies on some private message package.
