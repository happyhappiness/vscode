int mutt_parse_bind (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  const struct binding_t *bindings = NULL;
  char *key;
  int menu[sizeof(Menus)/sizeof(struct mapping_t)-1], r = 0, nummenus, i;

  if ((key = parse_keymap (menu, s, sizeof (menu)/sizeof (menu[0]),
			   &nummenus, err)) == NULL)
    return (-1);

  /* function to execute */
  mutt_extract_token (buf, s, 0);
  if (MoreArgs (s))
  {
    strfcpy (err->data, _("bind: too many arguments"), err->dsize);
    r = -1;
  }
  else if (ascii_strcasecmp ("noop", buf->data) == 0)
  {
    for (i = 0; i < nummenus; ++i)
    {
      km_bindkey (key, menu[i], OP_NULL); /* the `unbind' command */
    }
  }
  else
  {
    for (i = 0; i < nummenus; ++i)
    {
      /* First check the "generic" list of commands */
      if (menu[i] == MENU_PAGER || menu[i] == MENU_EDITOR ||
      menu[i] == MENU_GENERIC ||
	  try_bind (key, menu[i], buf->data, OpGeneric) != 0)
      {
        /* Now check the menu-specific list of commands (if they exist) */
        bindings = km_get_table (menu[i]);
        if (bindings && try_bind (key, menu[i], buf->data, bindings) != 0)
        {
          snprintf (err->data, err->dsize, _("%s: no such function in map"), buf->data);
          r = -1;
        }
      }
    }
  }
  FREE (&key);
  return (r);
}