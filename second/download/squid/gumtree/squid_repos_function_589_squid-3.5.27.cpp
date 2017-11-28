static int
load_deplibs (lt_dlhandle handle, char * deplibs LT__UNUSED)
{
  handle->depcount = 0;
  return 0;
}