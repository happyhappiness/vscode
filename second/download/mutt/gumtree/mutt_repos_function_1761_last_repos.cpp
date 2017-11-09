static int parse_unreplace_list (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  REPLACE_LIST **list = (REPLACE_LIST **)data;

  /* First token is a regexp. */
  if (!MoreArgs(s))
  {
    strfcpy(err->data, _("not enough arguments"), err->dsize);
    return -1;
  }

  mutt_extract_token(buf, s, 0);

  /* "*" is a special case. */
  if (!mutt_strcmp (buf->data, "*"))
  {
    mutt_free_replace_list (list);
    return 0;
  }

  remove_from_replace_list(list, buf->data);
  return 0;
}