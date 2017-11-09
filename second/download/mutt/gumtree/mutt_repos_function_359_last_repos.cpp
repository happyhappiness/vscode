int mutt_parse_push (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  int r = 0;

  mutt_extract_token (buf, s, MUTT_TOKEN_CONDENSE);
  if (MoreArgs (s))
  {
    strfcpy (err->data, _("push: too many arguments"), err->dsize);
    r = -1;
  }
  else
    tokenize_push_macro_string (buf->data);
  return (r);
}