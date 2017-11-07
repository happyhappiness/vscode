char *parse_keymap (int *menu, BUFFER *s, BUFFER *err)
{
  BUFFER buf;

  memset (&buf, 0, sizeof (buf));

  /* menu name */
  mutt_extract_token (&buf, s, 0);
  if (MoreArgs (s))
  {
    if ((*menu = mutt_check_menu (buf.data)) == -1)
    {
      snprintf (err->data, err->dsize, _("%s: no such menu"), buf.data);
    }
    else
    {
      /* key sequence */
      mutt_extract_token (&buf, s, 0);

      if (!*buf.data)
      {
	strfcpy (err->data, _("null key sequence"), err->dsize);
      }
      else if (MoreArgs (s))
	return (buf.data);
    }
  }
  else
  {
    strfcpy (err->data, _("too few arguments"), err->dsize);
  }
  FREE (&buf.data);
  return (NULL);
}