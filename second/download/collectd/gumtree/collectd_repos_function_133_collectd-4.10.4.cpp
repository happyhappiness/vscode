static int
vl_exit (lt_user_data LT__UNUSED loader_data)
{
  vtable = NULL;
  free_symlists ();
  return 0;
}