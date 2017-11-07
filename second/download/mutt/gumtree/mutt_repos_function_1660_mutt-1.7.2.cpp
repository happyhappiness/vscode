static int parse_list (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  do
  {
    mutt_extract_token (buf, s, 0);
    add_to_list ((LIST **) data, buf->data);
  }
  while (MoreArgs (s));

  return 0;
}