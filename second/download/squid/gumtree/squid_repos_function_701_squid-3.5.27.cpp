static void *
vm_sym (lt_user_data loader_data LT__UNUSED, lt_module module, const char *name)
{
  void *address = 0;
  image_id image = (image_id) module;

  if (get_image_symbol (image, name, B_SYMBOL_TYPE_ANY, address) != B_OK)
    {
      LT__SETERROR (SYMBOL_NOT_FOUND);
      address = 0;
    }

  return address;
}