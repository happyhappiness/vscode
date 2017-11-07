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
    /* ncurses doesn't return on resized screen when timeout is set to zero */
    if (menu != MENU_EDITOR)
      timeout ((Timeout > 0 ? Timeout : 60) * 1000);

    tmp = mutt_getch();

    if (menu != MENU_EDITOR)
      timeout (-1); /* restore blocking operation */

    LastKey = tmp.ch;
    if (LastKey == -1)
      return -1;

    /* do we have an op already? */
    if (tmp.op)
    {
      char *func = NULL;
      struct binding_t *bindings;

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
	    /* careful not to feed the <..> as one token. otherwise 
	    * push_string() will push the bogus op right back! */
	    mutt_ungetch ('>', 0);
	    push_string (func);
	    mutt_ungetch ('<', 0);
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

      if (n++ == 10)
      {
	mutt_flushinp ();
	mutt_error _("Macro loop detected.");
	return -1;
      }

      push_string (map->macro);
      map = Keymaps[menu];
      pos = 0;
    }
  }

  /* not reached */
}