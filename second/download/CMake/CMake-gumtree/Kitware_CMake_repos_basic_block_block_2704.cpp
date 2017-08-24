{
  int ret = choose_cuda_device();
  if (ret) {
    return 0;
  }

  int r1 = call_cuda_seperable_code(42);
  int r2 = mixed_launch_kernel(42);
  return (r1 == 42 || r2 == 42) ? 1 : 0;
}