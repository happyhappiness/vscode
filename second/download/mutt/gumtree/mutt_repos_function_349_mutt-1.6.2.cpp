static char *parse_keymap (int *menu, BUFFER *s, int maxmenus, int *nummenus, BUFFER *err)
{
  BUFFER buf;
  int i=0;
  char *p, *q;

  mutt_buffer_init (&buf);

  /* menu name */
  mutt_extract_token (&buf, s, 0);
  p = buf.data;
  if (MoreArgs (s))
  {
    while (i < maxmenus)
    {
      q = strchr(p,',');
      if (q)
        *q = '\0';

      if ((menu[i] = mutt_check_menu (p)) == -1)
      {
         snprintf (err->data, err->dsize, _("%s: no such menu"), p);
         goto error;
      }
      ++i;
      if (q)
        p = q+1;
      else
        break;
    }
    *nummenus=i;
    /* key sequence */
    mutt_extract_token (&buf, s, 0);

    if (!*buf.data)
    {
      strfcpy (err->data, _("null key sequence"), err->dsize);
    }
    else if (MoreArgs (s))
      return (buf.data);
  }
  else
  {
    strfcpy (err->data, _("too few arguments"), err->dsize);
  }
error:
  FREE (&buf.data);
  return (NULL);
}