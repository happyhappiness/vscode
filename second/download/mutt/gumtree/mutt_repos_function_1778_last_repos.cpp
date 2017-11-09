static int parse_subscribe (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  group_context_t *gc = NULL;
  
  do
  {
    mutt_extract_token (buf, s, 0);

    if (parse_group_context (&gc, buf, s, data, err) == -1)
      goto bail;
    
    mutt_remove_from_rx_list (&UnMailLists, buf->data);
    mutt_remove_from_rx_list (&UnSubscribedLists, buf->data);

    if (mutt_add_to_rx_list (&MailLists, buf->data, REG_ICASE, err) != 0)
      goto bail;
    if (mutt_add_to_rx_list (&SubscribedLists, buf->data, REG_ICASE, err) != 0)
      goto bail;
    if (mutt_group_context_add_rx (gc, buf->data, REG_ICASE, err) != 0)
      goto bail;
  }
  while (MoreArgs (s));
  
  mutt_group_context_destroy (&gc);
  return 0;
  
 bail:
  mutt_group_context_destroy (&gc);
  return -1;
}