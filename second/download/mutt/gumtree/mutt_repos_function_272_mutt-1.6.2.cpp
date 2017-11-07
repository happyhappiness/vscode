int mutt_parse_unhook (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  while (MoreArgs (s))
  {
    mutt_extract_token (buf, s, 0);
    if (mutt_strcmp ("*", buf->data) == 0)
    {
      if (current_hook_type)
      {
	snprintf (err->data, err->dsize,
		  _("unhook: Can't do unhook * from within a hook."));
	return -1;
      }
      delete_hooks (0);
    }
    else
    {
      int type = mutt_get_hook_type (buf->data);

      if (!type)
      {
	snprintf (err->data, err->dsize,
		 _("unhook: unknown hook type: %s"), buf->data);
	return (-1);
      }
      if (current_hook_type == type)
      {
	snprintf (err->data, err->dsize,
		  _("unhook: Can't delete a %s from within a %s."),
		  buf->data, buf->data);
	return -1;
      }
      delete_hooks (type);
    }
  }
  return 0;
}