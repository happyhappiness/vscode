static void query_menu (char *buf, size_t buflen, QUERY *results, int retbuf)
{
  MUTTMENU *menu;
  HEADER *msg = NULL;
  ENTRY *QueryTable = NULL;
  QUERY *queryp = NULL;
  int i, done = 0;
  int op;
  char helpstr[LONG_STRING];
  char title[STRING];

  snprintf (title, sizeof (title), _("Query")); /* FIXME */

  menu = mutt_new_menu (MENU_QUERY);
  menu->make_entry = query_entry;
  menu->search = query_search;
  menu->tag = query_tag;
  menu->title = title;
  menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_QUERY, QueryHelp);

  if (results == NULL)
  {
    /* Prompt for Query */
    if (mutt_get_field (_("Query: "), buf, buflen, 0) == 0 && buf[0])
    {
      results = run_query (buf, 0);
    }
  }

  if (results)
  {
    snprintf (title, sizeof (title), _("Query '%s'"), buf);

    /* count the number of results */
    for (queryp = results; queryp; queryp = queryp->next)
      menu->max++;

    menu->data = QueryTable = (ENTRY *) safe_calloc (menu->max, sizeof (ENTRY));

    for (i = 0, queryp = results; queryp; queryp = queryp->next, i++)
      QueryTable[i].data = queryp;

    while (!done)
    {
      switch ((op = mutt_menuLoop (menu)))
      {
	case OP_QUERY_APPEND:
	case OP_QUERY:
	  if (mutt_get_field (_("Query: "), buf, buflen, 0) == 0 && buf[0])
	  {
	    QUERY *newresults = NULL;

	    newresults = run_query (buf, 0);

	    menu->redraw = REDRAW_FULL;
	    if (newresults)
	    {
	      snprintf (title, sizeof (title), _("Query '%s'"), buf);

	      if (op == OP_QUERY)
	      {
                free_query (&results);
		results = newresults;
		FREE (&QueryTable);
	      }
	      else
	      {
		/* append */
		for (queryp = results; queryp->next; queryp = queryp->next);

		queryp->next = newresults;
	      }


	      menu->current = 0;
	      mutt_menuDestroy (&menu);
	      menu = mutt_new_menu (MENU_QUERY);
	      menu->make_entry = query_entry;
	      menu->search = query_search;
	      menu->tag = query_tag;
	      menu->title = title;
	      menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_QUERY, QueryHelp);

	      /* count the number of results */
	      for (queryp = results; queryp; queryp = queryp->next)
		menu->max++;

	      if (op == OP_QUERY)
	      {
		menu->data = QueryTable = 
		  (ENTRY *) safe_calloc (menu->max, sizeof (ENTRY));

		for (i = 0, queryp = results; queryp; 
		     queryp = queryp->next, i++)
		  QueryTable[i].data = queryp;
	      }
	      else
	      {
		int clear = 0;

		/* append */
		safe_realloc (&QueryTable, menu->max * sizeof (ENTRY));

		menu->data = QueryTable;

		for (i = 0, queryp = results; queryp; 
		     queryp = queryp->next, i++)
		{
		  /* once we hit new entries, clear/init the tag */
		  if (queryp == newresults)
		    clear = 1;

		  QueryTable[i].data = queryp;
		  if (clear)
		    QueryTable[i].tagged = 0;
		}
	      }
	    }
	  }
	  break;

	case OP_CREATE_ALIAS:
	  if (menu->tagprefix)
	  {
	    ADDRESS *naddr = NULL;

	    for (i = 0; i < menu->max; i++)
	      if (QueryTable[i].tagged)
	      {
		ADDRESS *a = result_to_addr(QueryTable[i].data);
		rfc822_append (&naddr, a, 0);
		rfc822_free_address (&a);
	      }

	    mutt_create_alias (NULL, naddr);
	  }
	  else
	  {
	    ADDRESS *a = result_to_addr(QueryTable[menu->current].data);
	    mutt_create_alias (NULL, a);
	    rfc822_free_address (&a);
	  }
	  break;

	case OP_GENERIC_SELECT_ENTRY:
	  if (retbuf)
	  {
	    done = 2;
	    break;
	  }
	  /* fall through to OP_MAIL */

	case OP_MAIL:
	  msg = mutt_new_header ();
	  msg->env = mutt_new_envelope ();
	  if (!menu->tagprefix)
	  {
	    msg->env->to = result_to_addr(QueryTable[menu->current].data);
	  }
	  else
	  {
	    for (i = 0; i < menu->max; i++)
	      if (QueryTable[i].tagged)
	      {
		ADDRESS *a = result_to_addr(QueryTable[i].data);
		rfc822_append (&msg->env->to, a, 0);
		rfc822_free_address (&a);
	      }
	  }
	  ci_send_message (0, msg, NULL, Context, NULL);
	  menu->redraw = REDRAW_FULL;
	  break;

	case OP_EXIT:
	  done = 1;
	  break;
      }
    }

    /* if we need to return the selected entries */
    if (retbuf && (done == 2))
    {
      int tagged = 0;
      size_t curpos = 0;

      memset (buf, 0, buflen); 

      /* check for tagged entries */
      for (i = 0; i < menu->max; i++)
      {
	if (QueryTable[i].tagged)
	{
	  if (curpos == 0)
	  {
	    ADDRESS *tmpa = result_to_addr (QueryTable[i].data);
	    mutt_addrlist_to_local (tmpa);
	    tagged = 1;
	    rfc822_write_address (buf, buflen, tmpa, 0);
	    curpos = mutt_strlen (buf);
	    rfc822_free_address (&tmpa);
	  }
	  else if (curpos + 2 < buflen)
	  {
	    ADDRESS *tmpa = result_to_addr (QueryTable[i].data);
	    mutt_addrlist_to_local (tmpa);
	    strcat (buf, ", ");	/* __STRCAT_CHECKED__ */
	    rfc822_write_address ((char *) buf + curpos + 1, buflen - curpos - 1,
				  tmpa, 0);
	    curpos = mutt_strlen (buf);
	    rfc822_free_address (&tmpa);
	  }
	}
      }
      /* then enter current message */
      if (!tagged)
      {
	ADDRESS *tmpa = result_to_addr (QueryTable[menu->current].data);
	mutt_addrlist_to_local (tmpa);
	rfc822_write_address (buf, buflen, tmpa, 0);
	rfc822_free_address (&tmpa);
      }
      
    }

    free_query (&results);
    FREE (&QueryTable);
    
    /* tell whoever called me to redraw the screen when I return */
    set_option (OPTNEEDREDRAW);
  }

  mutt_menuDestroy (&menu);
}