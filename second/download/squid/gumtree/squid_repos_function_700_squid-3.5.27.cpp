static int
vm_close (lt_user_data loader_data LT__UNUSED, lt_module module)
{
  int errors = 0;

  if (unload_add_on ((image_id) module) != B_OK)
    {
      LT__SETERROR (CANNOT_CLOSE);
      ++errors;
    }

  return errors;
}