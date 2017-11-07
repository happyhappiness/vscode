static int parse_unlists (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  do
  {
    mutt_extract_token (buf, s, 0);
    mutt_remove_from_rx_list (&SubscribedLists, buf->data);
    mutt_remove_from_rx_list (&MailLists, buf->data);
    
    if (mutt_strcmp (buf->data, "*") && 
	mutt_add_to_rx_list (&UnMailLists, buf->data, REG_ICASE, err) != 0)
      return -1;
  }
  while (MoreArgs (s));

  return 0;
}