static int
vm_close (lt_user_data loader_data LT__UNUSED, lt_module module LT__UNUSED)
{
  /* Just to silence gcc -Wall */
  module = 0;
  return 0;
}