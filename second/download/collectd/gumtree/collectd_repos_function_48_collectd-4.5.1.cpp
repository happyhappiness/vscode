static lt_module
presym_open (loader_data, filename)
     lt_user_data loader_data;
     const char *filename;
{
  lt_dlsymlists_t *lists;
  lt_module	   module = (lt_module) 0;

  LT_DLMUTEX_LOCK ();
  lists = preloaded_symbols;

  if (!lists)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (NO_SYMBOLS));
      goto done;
    }

  /* Can't use NULL as the reflective symbol header, as NULL is
     used to mark the end of the entire symbol list.  Self-dlpreopened
     symbols follow this magic number, chosen to be an unlikely
     clash with a real module name.  */
  if (!filename)
    {
      filename = "@PROGRAM@";
    }

  while (lists)
    {
      const lt_dlsymlist *syms = lists->syms;

      while (syms->name)
	{
	  if (!syms->address && strcmp(syms->name, filename) == 0)
	    {
	      module = (lt_module) syms;
	      goto done;
	    }
	  ++syms;
	}

      lists = lists->next;
    }

  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (FILE_NOT_FOUND));

 done:
  LT_DLMUTEX_UNLOCK ();
  return module;
}