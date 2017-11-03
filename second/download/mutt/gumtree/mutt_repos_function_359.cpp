int mutt_parse_macro (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  int menu[sizeof(Menus)/sizeof(struct mapping_t)-1], r = -1, nummenus, i;
  char *seq = NULL;
  char *key;

  if ((key = parse_keymap (menu, s, sizeof (menu) / sizeof (menu[0]), &nummenus, err)) == NULL)
    return (-1);

  mutt_extract_token (buf, s, MUTT_TOKEN_CONDENSE);
  /* make sure the macro sequence is not an empty string */
  if (!*buf->data)
  {
    strfcpy (err->data, _("macro: empty key sequence"), err->dsize);
  }
  else
  {
    if (MoreArgs (s))
    {
      seq = safe_strdup (buf->data);
      mutt_extract_token (buf, s, MUTT_TOKEN_CONDENSE);

      if (MoreArgs (s))
      {
	strfcpy (err->data, _("macro: too many arguments"), err->dsize);
      }
      else
      {
        for (i = 0; i < nummenus; ++i)
        {
          km_bind (key, menu[i], OP_MACRO, seq, buf->data);
          r = 0;
        }
      }

      FREE (&seq);
    }
    else
    {
      for (i = 0; i < nummenus; ++i)
      {
        km_bind (key, menu[i], OP_MACRO, buf->data, NULL);
        r = 0;
      }
    }
  }
  FREE (&key);
  return (r);
}