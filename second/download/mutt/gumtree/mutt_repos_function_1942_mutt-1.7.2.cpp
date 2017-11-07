static int imap_open_new_message (MESSAGE *msg, CONTEXT *dest, HEADER *hdr)
{
  char tmp[_POSIX_PATH_MAX];

  mutt_mktemp (tmp, sizeof (tmp));
  if ((msg->fp = safe_fopen (tmp, "w")) == NULL)
  {
    mutt_perror (tmp);
    return (-1);
  }
  msg->path = safe_strdup(tmp);
  return 0;
}