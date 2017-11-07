int mutt_parse_bind (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  struct binding_t *bindings = NULL;
  char *key;
  int menu, r = 0;

  if ((key = parse_keymap (&menu, s, err)) == NULL)
    return (-1);

  /* function to execute */
  mutt_extract_token (buf, s, 0);
  if (MoreArgs (s))
  {
    strfcpy (err->data, _("bind: too many arguments"), err->dsize);
    r = -1;
  }
  else if (ascii_strcasecmp ("noop", buf->data) == 0)
    km_bindkey (key, menu, OP_NULL); /* the `unbind' command */
  else
  {
    /* First check the "generic" list of commands */
    if (menu == MENU_PAGER || menu == MENU_EDITOR || menu == MENU_GENERIC ||
	try_bind (key, menu, buf->data, OpGeneric) != 0)
    {
      /* Now check the menu-specific list of commands (if they exist) */
      bindings = km_get_table (menu);
      if (bindings && try_bind (key, menu, buf->data, bindings) != 0)
      {
	snprintf (err->data, err->dsize, _("%s: no such function in map"), buf->data);
	r = -1;
      }
    }
  }
  FREE (&key);
  return (r);
}