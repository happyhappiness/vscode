void mutt_alias_menu (char *buf, size_t buflen, ALIAS *aliases)
{
  ALIAS *aliasp;
  MUTTMENU *menu;
  ALIAS **AliasTable = NULL;
  int t = -1;
  int i, done = 0;
  int op;
  char helpstr[LONG_STRING];

  int omax;
  
  if (!aliases)
  {
    mutt_error _("You have no aliases!");
    return;
  }

  menu = mutt_new_menu (MENU_ALIAS);
  menu->make_entry = alias_entry;
  menu->tag = alias_tag;
  menu->title = _("Aliases");
  menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_ALIAS, AliasHelp);
  mutt_push_current_menu (menu);

new_aliases:

  omax = menu->max;
  
  /* count the number of aliases */
  for (aliasp = aliases; aliasp; aliasp = aliasp->next)
  {
    aliasp->self->del    = 0;
    aliasp->self->tagged = 0;
    menu->max++;
  }

  safe_realloc (&AliasTable, menu->max * sizeof (ALIAS *));
  menu->data = AliasTable;

  for (i = omax, aliasp = aliases; aliasp; aliasp = aliasp->next, i++)
  {
    AliasTable[i] = aliasp->self;
    aliases       = aliasp;
  }

  if ((SortAlias & SORT_MASK) != SORT_ORDER)
  {
    qsort (AliasTable, i, sizeof (ALIAS *),
	 (SortAlias & SORT_MASK) == SORT_ADDRESS ? alias_SortAddress : alias_SortAlias);
  }

  for (i=0; i<menu->max; i++) AliasTable[i]->num = i;

  while (!done)
  {
    if (aliases->next)
    {
      menu->redraw |= REDRAW_FULL;
      aliases       = aliases->next;
      goto new_aliases;
    }
    
    switch ((op = mutt_menuLoop (menu)))
    {
      case OP_DELETE:
      case OP_UNDELETE:
        if (menu->tagprefix)
        {
	  for (i = 0; i < menu->max; i++)
	    if (AliasTable[i]->tagged)
	      AliasTable[i]->del = (op == OP_DELETE) ? 1 : 0;
	  menu->redraw |= REDRAW_INDEX;
	}
        else
        {
	  AliasTable[menu->current]->self->del = (op == OP_DELETE) ? 1 : 0;
	  menu->redraw |= REDRAW_CURRENT;
	  if (option (OPTRESOLVE) && menu->current < menu->max - 1)
	  {
	    menu->current++;
	    menu->redraw |= REDRAW_INDEX;
	  }
	}
        break;
      case OP_GENERIC_SELECT_ENTRY:
        t = menu->current;
      case OP_EXIT:
	done = 1;
	break;
    }
  }

  for (i = 0; i < menu->max; i++)
  {
    if (AliasTable[i]->tagged)
    {
      rfc822_write_address (buf, buflen, AliasTable[i]->addr, 1);
      t = -1;
    }
  }

  if (t != -1)
  {
    rfc822_write_address (buf, buflen, AliasTable[t]->addr, 1);
  }

  mutt_pop_current_menu (menu);
  mutt_menuDestroy (&menu);
  FREE (&AliasTable);
  
}