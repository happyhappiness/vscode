static int parse_unalternates (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  _alternates_clean();
  do
  {
    mutt_extract_token (buf, s, 0);
    mutt_remove_from_rx_list (&Alternates, buf->data);

    if (mutt_strcmp (buf->data, "*") &&
	mutt_add_to_rx_list (&UnAlternates, buf->data, REG_ICASE, err) != 0)
      return -1;

  }
  while (MoreArgs (s));

  return 0;
}