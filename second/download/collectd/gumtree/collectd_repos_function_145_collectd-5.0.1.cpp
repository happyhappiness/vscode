static int
vm_close (lt_user_data LT__UNUSED loader_data, lt_module module)
{
  int errors = 0;

  if (dlclose (module) != 0)
    {
      DL__SETERROR (CANNOT_CLOSE);
      ++errors;
    }

  return errors;
}