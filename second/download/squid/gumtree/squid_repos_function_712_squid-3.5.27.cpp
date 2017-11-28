int
lt_dlpreload_open (const char *originator, lt_dlpreload_callback_func *func)
{
  symlist_chain *list;
  int		 errors = 0;
  int		 found  = 0;

  /* For each symlist in the chain...  */
  for (list = preloaded_symlists; list; list = list->next)
    {
      /* ...that was preloaded by the requesting ORIGINATOR... */
      if ((originator && STREQ (list->symlist->name, originator))
          || (!originator && STREQ (list->symlist->name, "@PROGRAM@")))
	{
	  const lt_dlsymlist *symbol;
	  unsigned int idx = 0;

	  ++found;

	  /* ...load the symbols per source compilation unit:
	     (we preincrement the index to skip over the originator entry)  */
	  while ((symbol = &list->symlist[++idx])->name != 0)
	    {
	      if ((symbol->address == 0)
		  && (STRNEQ (symbol->name, "@PROGRAM@")))
		{
		  lt_dlhandle handle = lt_dlopen (symbol->name);
		  if (handle == 0)
		    {
		      ++errors;
		    }
		  else
		    {
		      errors += (*func) (handle);
		    }
		}
	    }
	}
    }

  if (!found)
    {
      LT__SETERROR(CANNOT_OPEN);
      ++errors;
    }

  return errors;
}