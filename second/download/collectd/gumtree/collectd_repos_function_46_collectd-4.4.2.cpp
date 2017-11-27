static int
presym_exit (loader_data)
     lt_user_data loader_data;
{
  presym_free_symlists ();
  return 0;
}