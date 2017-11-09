static int parse_path_list (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  char path[_POSIX_PATH_MAX];

  do
  {
    mutt_extract_token (buf, s, 0);
    strfcpy (path, buf->data, sizeof (path));
    mutt_expand_path (path, sizeof (path));
    add_to_list ((LIST **) data, path);
  }
  while (MoreArgs (s));

  return 0;
}