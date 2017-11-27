static lt_ptr
sys_bedl_sym (loader_data, module, symbol)
     lt_user_data loader_data;
     lt_module module;
     const char *symbol;
{
  lt_ptr address = 0;
  image_id image = (image_id) module;

  if (get_image_symbol (image, symbol, B_SYMBOL_TYPE_ANY, address) != B_OK)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (SYMBOL_NOT_FOUND));
      address = 0;
    }

  return address;
}