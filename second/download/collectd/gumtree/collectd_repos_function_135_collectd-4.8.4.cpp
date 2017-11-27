static int
vm_close (lt_user_data LT__UNUSED loader_data, lt_module LT__UNUSED module)
{
  /* Just to silence gcc -Wall */
  module = 0;
  return 0;
}