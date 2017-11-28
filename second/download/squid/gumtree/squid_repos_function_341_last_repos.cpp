static int
vm_close (lt_user_data loader_data LT__UNUSED, lt_module module)
{
  int errors = 0;

  if (FreeLibrary ((HMODULE) module) == 0)
    {
      LOADLIB_SETERROR (CANNOT_CLOSE);
      ++errors;
    }

  return errors;
}