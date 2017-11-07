static int parse_my_hdr (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  LIST *tmp;
  size_t keylen;
  char *p;

  mutt_extract_token (buf, s, M_TOKEN_SPACE | M_TOKEN_QUOTE);
  if ((p = strpbrk (buf->data, ": \t")) == NULL || *p != ':')
  {
    strfcpy (err->data, _("invalid header field"), err->dsize);
    return (-1);
  }
  keylen = p - buf->data + 1;

  if (UserHeader)
  {
    for (tmp = UserHeader; ; tmp = tmp->next)
    {
      /* see if there is already a field by this name */
      if (ascii_strncasecmp (buf->data, tmp->data, keylen) == 0)
      {
	/* replace the old value */
	safe_free ((void **) &tmp->data);
	tmp->data = buf->data;
	memset (buf, 0, sizeof (BUFFER));
	return 0;
      }
      if (!tmp->next)
	break;
    }
    tmp->next = mutt_new_list ();
    tmp = tmp->next;
  }
  else
  {
    tmp = mutt_new_list ();
    UserHeader = tmp;
  }
  tmp->data = buf->data;
  memset (buf, 0, sizeof (BUFFER));
  return 0;
}