static int parse_unlist (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  do
  {
    mutt_extract_token (buf, s, 0);
    /*
     * Check for deletion of entire list
     */
    if (mutt_strcmp (buf->data, "*") == 0)
    {
      mutt_free_list ((LIST **) data);
      break;
    }
    remove_from_list ((LIST **) data, buf->data);
  }
  while (MoreArgs (s));

  return 0;
}