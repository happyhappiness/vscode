static int parse_unlist (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  do
  {
    mutt_extract_token (buf, s, 0);
    remove_from_list ((LIST **) data, buf->data);
  }
  while (MoreArgs (s));

  return 0;
}