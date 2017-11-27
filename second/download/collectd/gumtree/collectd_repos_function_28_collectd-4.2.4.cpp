static lt_ptr
sys_wll_sym (loader_data, module, symbol)
     lt_user_data loader_data;
     lt_module module;
     const char *symbol;
{
  lt_ptr      address  = GetProcAddress (module, symbol);

  if (!address)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (SYMBOL_NOT_FOUND));
    }

  return address;
}