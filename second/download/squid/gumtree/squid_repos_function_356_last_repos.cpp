static int
vm_close (lt_user_data loader_data LT__UNUSED, lt_module module)
{
  int errors = 0;

  if (module && (shl_unload ((shl_t) (module)) != 0))
    {
      LT__SETERROR (CANNOT_CLOSE);
      ++errors;
    }

  return errors;
}