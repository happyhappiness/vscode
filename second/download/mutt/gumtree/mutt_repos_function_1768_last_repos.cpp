static int parse_path_unlist (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  char path[_POSIX_PATH_MAX];

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
    strfcpy (path, buf->data, sizeof (path));
    mutt_expand_path (path, sizeof (path));
    remove_from_list ((LIST **) data, path);
  }
  while (MoreArgs (s));

  return 0;
}