static int
presym_close (loader_data, module)
     lt_user_data loader_data;
     lt_module module;
{
  /* Just to silence gcc -Wall */
  module = 0;
  return 0;
}