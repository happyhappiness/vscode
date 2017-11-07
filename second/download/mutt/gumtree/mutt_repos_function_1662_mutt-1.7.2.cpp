static int parse_alternates (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  group_context_t *gc = NULL;
  
  _alternates_clean();

  do
  {
    mutt_extract_token (buf, s, 0);

    if (parse_group_context (&gc, buf, s, data, err) == -1)
      goto bail;

    mutt_remove_from_rx_list (&UnAlternates, buf->data);

    if (mutt_add_to_rx_list (&Alternates, buf->data, REG_ICASE, err) != 0)
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