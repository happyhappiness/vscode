MODULE_EXPORT int MODULE_CCONV example_mod_1_function(int n)
{
  int result = example_exe_function() + n;
  printf("world\n");
  return result;
}