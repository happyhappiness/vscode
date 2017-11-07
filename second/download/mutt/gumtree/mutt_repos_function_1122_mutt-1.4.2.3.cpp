static int parse_subscribe (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  do
  {
    mutt_extract_token (buf, s, 0);
    add_to_list (&MailLists, buf->data);
    add_to_list (&SubscribedLists, buf->data);
  }
  while (MoreArgs (s));

  return 0;
}