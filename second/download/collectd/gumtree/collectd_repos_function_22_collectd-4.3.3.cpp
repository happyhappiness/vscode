static lt_ptr
sys_dl_sym (loader_data, module, symbol)
     lt_user_data loader_data;
     lt_module module;
     const char *symbol;
{
  lt_ptr address = dlsym (module, symbol);

  if (!address)
    {
      LT_DLMUTEX_SETERROR (DLERROR (SYMBOL_NOT_FOUND));
    }

  return address;
}