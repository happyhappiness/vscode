static int parse_alias (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  ALIAS *tmp = Aliases;
  ALIAS *last = NULL;
  char *estr = NULL;
  group_context_t *gc = NULL;
  
  if (!MoreArgs (s))
  {
    strfcpy (err->data, _("alias: no address"), err->dsize);
    return (-1);
  }

  mutt_extract_token (buf, s, 0);

  if (parse_group_context (&gc, buf, s, data, err) == -1)
    return -1;
  
  /* check to see if an alias with this name already exists */
  for (; tmp; tmp = tmp->next)
  {
    if (!mutt_strcasecmp (tmp->name, buf->data))
      break;
    last = tmp;
  }

  if (!tmp)
  {
    /* create a new alias */
    tmp = (ALIAS *) safe_calloc (1, sizeof (ALIAS));
    tmp->self = tmp;
    tmp->name = safe_strdup (buf->data);
    /* give the main addressbook code a chance */
    if (CurrentMenu == MENU_ALIAS)
      set_option (OPTMENUCALLER);
  }
  else
  {
    mutt_alias_delete_reverse (tmp);
    /* override the previous value */
    rfc822_free_address (&tmp->addr);
    if (CurrentMenu == MENU_ALIAS)
      mutt_set_current_menu_redraw_full ();
  }

  mutt_extract_token (buf, s, MUTT_TOKEN_QUOTE | MUTT_TOKEN_SPACE | MUTT_TOKEN_SEMICOLON);
  dprint (3, (debugfile, "parse_alias: Second token is '%s'.\n",
	      buf->data));

  tmp->addr = mutt_parse_adrlist (tmp->addr, buf->data);

  if (last)
    last->next = tmp;
  else
    Aliases = tmp;
  if (mutt_addrlist_to_intl (tmp->addr, &estr))
  {
    snprintf (err->data, err->dsize, _("Warning: Bad IDN '%s' in alias '%s'.\n"),
	      estr, tmp->name);
    goto bail;
  }

  mutt_group_context_add_adrlist (gc, tmp->addr);
  mutt_alias_add_reverse (tmp);

#ifdef DEBUG
  if (debuglevel >= 2) 
  {
    ADDRESS *a;
    /* A group is terminated with an empty address, so check a->mailbox */
    for (a = tmp->addr; a && a->mailbox; a = a->next)
    {
      if (!a->group)
	dprint (3, (debugfile, "parse_alias:   %s\n",
		    a->mailbox));
      else
	dprint (3, (debugfile, "parse_alias:   Group %s\n",
		    a->mailbox));
    }
  }
#endif
  mutt_group_context_destroy (&gc);
  return 0;
  
  bail:
  mutt_group_context_destroy (&gc);
  return -1;
}