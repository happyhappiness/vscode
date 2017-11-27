static int
vl_exit (lt_user_data LT__UNUSED loader_data)
{
  vtable = NULL;
  LOCALFREE (error_message);
  return 0;
}