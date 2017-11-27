static int
presym_add_symlist (preloaded)
     const lt_dlsymlist *preloaded;
{
  lt_dlsymlists_t *tmp;
  lt_dlsymlists_t *lists;
  int		   errors   = 0;

  LT_DLMUTEX_LOCK ();

  lists = preloaded_symbols;
  while (lists)
    {
      if (lists->syms == preloaded)
	{
	  goto done;
	}
      lists = lists->next;
    }

  tmp = LT_EMALLOC (lt_dlsymlists_t, 1);
  if (tmp)
    {
      memset (tmp, 0, sizeof(lt_dlsymlists_t));
      tmp->syms = preloaded;
      tmp->next = preloaded_symbols;
      preloaded_symbols = tmp;
    }
  else
    {
      ++errors;
    }

 done:
  LT_DLMUTEX_UNLOCK ();
  return errors;
}