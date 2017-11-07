static int
parse_unmy_hdr (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  LIST *last = NULL;
  LIST *tmp = UserHeader;
  LIST *ptr;
  size_t l;

  do
  {
    mutt_extract_token (buf, s, 0);
    if (mutt_strcmp ("*", buf->data) == 0)
      mutt_free_list (&UserHeader);
    else
    {
      tmp = UserHeader;
      last = NULL;

      l = mutt_strlen (buf->data);
      if (buf->data[l - 1] == ':')
	l--;

      while (tmp)
      {
	if (ascii_strncasecmp (buf->data, tmp->data, l) == 0 && tmp->data[l] == ':')
	{
	  ptr = tmp;
	  if (last)
	    last->next = tmp->next;
	  else
	    UserHeader = tmp->next;
	  tmp = tmp->next;
	  ptr->next = NULL;
	  mutt_free_list (&ptr);
	}
	else
	{
	  last = tmp;
	  tmp = tmp->next;
	}
      }
    }
  }
  while (MoreArgs (s));
  return 0;
}