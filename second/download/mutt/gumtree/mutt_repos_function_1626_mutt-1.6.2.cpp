static int parse_unignore (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  do
  {
    mutt_extract_token (buf, s, 0);

    /* don't add "*" to the unignore list */
    if (strcmp (buf->data, "*")) 
      add_to_list (&UnIgnore, buf->data);

    remove_from_list (&Ignore, buf->data);
  }
  while (MoreArgs (s));

  return 0;
}