int km_dokey (int menu)
{
  event_t tmp;
  struct keymap_t *map = Keymaps[menu];
  int pos = 0;
  int n = 0;
  int i;

  if (!map)
    return (retry_generic (menu, NULL, 0, 0));

  FOREVER
  {
    i = Timeout > 0 ? Timeout : 60;
#ifdef USE_IMAP
    /* keepalive may need to run more frequently than Timeout allows */
    if (ImapKeepalive)
    {
      if (ImapKeepalive >= i)
      	imap_keepalive ();
      else
	while (ImapKeepalive && ImapKeepalive < i)
	{
	  timeout (ImapKeepalive * 1000);
	  tmp = mutt_getch ();
	  timeout (-1);
	  /* If a timeout was not received, or the window was resized, exit the
	   * loop now.  Otherwise, continue to loop until reaching a total of
	   * $timeout seconds.
	   */
	  if (tmp.ch != -2 || SigWinch)
	    goto gotkey;
	  i -= ImapKeepalive;
	  imap_keepalive ();
	}
    }
#endif

    timeout (i * 1000);
    tmp = mutt_getch();
    timeout (-1);

    /* hide timeouts from line editor */
    if (menu == MENU_EDITOR && tmp.ch == -2)
      continue;

#ifdef USE_IMAP
  gotkey:
#endif
    LastKey = tmp.ch;
    if (LastKey < 0)
      return -1;

    /* do we have an op already? */
    if (tmp.op)
    {
      char *func = NULL;
      const struct binding_t *bindings;

      /* is this a valid op for this menu? */
      if ((bindings = km_get_table (menu)) &&
	  (func = get_func (bindings, tmp.op)))
	return tmp.op;

      if (menu == MENU_EDITOR && get_func (OpEditor, tmp.op))
	return tmp.op;

      if (menu != MENU_EDITOR && menu != MENU_PAGER)
      {
	/* check generic menu */
	bindings = OpGeneric; 
	if ((func = get_func (bindings, tmp.op)))
	  return tmp.op;
      }

      /* Sigh. Valid function but not in this context.
       * Find the literal string and push it back */
      for (i = 0; Menus[i].name; i++)
      {
	bindings = km_get_table (Menus[i].value);
	if (bindings)
	{
	  func = get_func (bindings, tmp.op);
	  if (func)
	  {
	    mutt_unget_event ('>', 0);
	    mutt_unget_string (func);
	    mutt_unget_event ('<', 0);
	    break;
	  }
	}
      }
      /* continue to chew */
      if (func)
	continue;
    }

    /* Nope. Business as usual */
    while (LastKey > map->keys[pos])
    {
      if (pos > map->eq || !map->next)
	return (retry_generic (menu, map->keys, pos, LastKey));
      map = map->next;
    }

    if (LastKey != map->keys[pos])
      return (retry_generic (menu, map->keys, pos, LastKey));

    if (++pos == map->len)
    {

      if (map->op != OP_MACRO)
	return map->op;

      if (option (OPTIGNOREMACROEVENTS))
      {
	mutt_error _("Macros are currently disabled.");
	return -1;
      }

      if (n++ == 10)
      {
	mutt_flushinp ();
	mutt_error _("Macro loop detected.");
	return -1;
      }

      tokenize_push_macro_string (map->macro);
      map = Keymaps[menu];
      pos = 0;
    }
  }

  /* not reached */
}