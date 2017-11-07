static int parse_alias (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  ALIAS *tmp = Aliases;
  ALIAS *last = NULL;
  char *p;
  size_t len;

  if ((p = strpbrk (s->dptr, " \t")) == NULL)
  {
    strfcpy (err->data, _("alias: no address"), err->dsize);
    return (-1);
  }

  len = p - s->dptr;

  /* check to see if an alias with this name already exists */
  for (; tmp; tmp = tmp->next)
  {
    if (!mutt_strncasecmp (tmp->name, s->dptr, len) && *(tmp->name + len) == 0)
      break;
    last = tmp;
  }

  if (!tmp)
  {
    /* create a new alias */
    tmp = (ALIAS *) safe_calloc (1, sizeof (ALIAS));
    tmp->self = tmp;
    tmp->name = safe_malloc (len + 1);
    memcpy (tmp->name, s->dptr, len);
    tmp->name[len] = 0;
    /* give the main addressbook code a chance */
    if (CurrentMenu == MENU_ALIAS)
      set_option (OPTMENUCALLER);
  }
  else
  {
    /* override the previous value */
    rfc822_free_address (&tmp->addr);
    if (CurrentMenu == MENU_ALIAS)
      set_option (OPTFORCEREDRAWINDEX);
  }
  s->dptr = p;

  mutt_extract_token (buf, s, M_TOKEN_QUOTE | M_TOKEN_SPACE | M_TOKEN_SEMICOLON);
  tmp->addr = mutt_parse_adrlist (tmp->addr, buf->data);
  if (last)
    last->next = tmp;
  else
    Aliases = tmp;
  return 0;
}