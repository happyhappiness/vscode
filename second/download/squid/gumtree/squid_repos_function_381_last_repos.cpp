static int
add_symlist (const lt_dlsymlist *symlist)
{
  symlist_chain *lists;
  int		 errors   = 0;

  /* Search for duplicate entries:  */
  for (lists = preloaded_symlists;
       lists && lists->symlist != symlist; lists = lists->next)
    /*NOWORK*/;

  /* Don't add the same list twice:  */
  if (!lists)
    {
      symlist_chain *tmp = (symlist_chain *) lt__zalloc (sizeof *tmp);

      if (tmp)
	{
	  tmp->symlist = symlist;
	  tmp->next = preloaded_symlists;
	  preloaded_symlists = tmp;

	  if (symlist[1].name && STREQ (symlist[1].name, "@INIT@"))
	    {
	      void (*init_symlist)(void);
	      *(void **)(&init_symlist) = symlist[1].address;
	      (*init_symlist)();
	    }
	}
      else
	{
	  ++errors;
	}
    }

  return errors;
}