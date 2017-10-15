    expire = mutt_parse_date (expiration, NULL);
  else
    expire = -1;

  if (!ascii_strcasecmp (access_type, "x-mutt-deleted"))
  {
    if (s->flags & (MUTT_DISPLAY|MUTT_PRINTING))
    {
      char *length;
      char pretty_size[10];
      
      state_mark_attach (s);
      state_printf (s, _("[-- This %s/%s attachment "),
