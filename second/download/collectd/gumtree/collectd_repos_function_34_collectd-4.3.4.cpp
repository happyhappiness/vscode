static lt_ptr
sys_dld_sym (loader_data, module, symbol)
     lt_user_data loader_data;
     lt_module module;
     const char *symbol;
{
  lt_ptr address = dld_get_func (symbol);

  if (!address)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (SYMBOL_NOT_FOUND));
    }

  return address;
}