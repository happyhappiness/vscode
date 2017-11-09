static int parse_replace_list (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  REPLACE_LIST **list = (REPLACE_LIST **)data;
  BUFFER templ;

  memset(&templ, 0, sizeof(templ));

  /* First token is a regexp. */
  if (!MoreArgs(s))
  {
    strfcpy(err->data, _("not enough arguments"), err->dsize);
    return -1;
  }
  mutt_extract_token(buf, s, 0);

  /* Second token is a replacement template */
  if (!MoreArgs(s))
  {
    strfcpy(err->data, _("not enough arguments"), err->dsize);
    return -1;
  }
  mutt_extract_token(&templ, s, 0);

  if (add_to_replace_list(list, buf->data, templ.data, err) != 0) {
    FREE(&templ.data);
    return -1;
  }
  FREE(&templ.data);

  return 0;
}