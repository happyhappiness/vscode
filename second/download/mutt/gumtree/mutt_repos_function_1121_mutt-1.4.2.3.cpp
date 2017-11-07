static int parse_unlists (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  do
  {
    mutt_extract_token (buf, s, 0);
    remove_from_list (&MailLists, buf->data);
    remove_from_list (&SubscribedLists, buf->data);
  }
  while (MoreArgs (s));

  return 0;
}