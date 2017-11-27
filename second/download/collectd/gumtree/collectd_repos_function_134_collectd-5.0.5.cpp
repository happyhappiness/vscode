static lt_module
vm_open (lt_user_data LT__UNUSED loader_data, const char *filename,
         lt_dladvise LT__UNUSED advise)
{
  symlist_chain *lists;
  lt_module	 module = 0;

  if (!preloaded_symlists)
    {
      LT__SETERROR (NO_SYMBOLS);
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

  for (lists = preloaded_symlists; lists; lists = lists->next)
    {
      const lt_dlsymlist *symbol;
      for (symbol= lists->symlist; symbol->name; ++symbol)
	{
	  if (!symbol->address && streq (symbol->name, filename))
	    {
	      /* If the next symbol's name and address is 0, it means
		 the module just contains the originator and no symbols.
		 In this case we pretend that we never saw the module and
	         hope that some other loader will be able to load the module
	         and have access to its symbols */
	      const lt_dlsymlist *next_symbol = symbol +1;
	      if (next_symbol->address && next_symbol->name)
		{
	          module = (lt_module) lists->symlist;
	          goto done;
		}
	    }
	}
    }

  LT__SETERROR (FILE_NOT_FOUND);

 done:
  return module;
}