lt_ptr
lt_dlsym (handle, symbol)
     lt_dlhandle handle;
     const char *symbol;
{
  size_t lensym;
  char	lsym[LT_SYMBOL_LENGTH];
  char	*sym;
  lt_ptr address;
  lt_user_data data;

  if (!handle)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_HANDLE));
      return 0;
    }

  if (!symbol)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (SYMBOL_NOT_FOUND));
      return 0;
    }

  lensym = LT_STRLEN (symbol) + LT_STRLEN (handle->loader->sym_prefix)
					+ LT_STRLEN (handle->info.name);

  if (lensym + LT_SYMBOL_OVERHEAD < LT_SYMBOL_LENGTH)
    {
      sym = lsym;
    }
  else
    {
      sym = LT_EMALLOC (char, lensym + LT_SYMBOL_OVERHEAD + 1);
      if (!sym)
	{
	  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (BUFFER_OVERFLOW));
	  return 0;
	}
    }

  data = handle->loader->dlloader_data;
  if (handle->info.name)
    {
      const char *saved_error;

      LT_DLMUTEX_GETERROR (saved_error);

      /* this is a libtool module */
      if (handle->loader->sym_prefix)
	{
	  strcpy(sym, handle->loader->sym_prefix);
	  strcat(sym, handle->info.name);
	}
      else
	{
	  strcpy(sym, handle->info.name);
	}

      strcat(sym, "_LTX_");
      strcat(sym, symbol);

      /* try "modulename_LTX_symbol" */
      address = handle->loader->find_sym (data, handle->module, sym);
      if (address)
	{
	  if (sym != lsym)
	    {
	      LT_DLFREE (sym);
	    }
	  return address;
	}
      LT_DLMUTEX_SETERROR (saved_error);
    }

  /* otherwise try "symbol" */
  if (handle->loader->sym_prefix)
    {
      strcpy(sym, handle->loader->sym_prefix);
      strcat(sym, symbol);
    }
  else
    {
      strcpy(sym, symbol);
    }

  address = handle->loader->find_sym (data, handle->module, sym);
  if (sym != lsym)
    {
      LT_DLFREE (sym);
    }

  return address;
}