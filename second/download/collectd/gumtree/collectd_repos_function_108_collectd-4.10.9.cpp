static int
vm_close (lt_user_data LT__UNUSED loader_data, lt_module module)
{
  int errors = 0;

  if (dld_unlink_by_file ((char*)(module), 1) != 0)
    {
      LT__SETERROR (CANNOT_CLOSE);
      ++errors;
    }
  else
    {
      FREE (module);
    }

  return errors;
}