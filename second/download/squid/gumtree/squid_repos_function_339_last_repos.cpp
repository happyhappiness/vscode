static int
vl_exit (lt_user_data loader_data LT__UNUSED)
{
  vtable = NULL;
  LOCALFREE (error_message);
  return 0;
}