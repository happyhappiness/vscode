static int mmdf_commit_message (CONTEXT *ctx, MESSAGE *msg)
{
  if (fputs (MMDF_SEP, msg->fp) == EOF)
    return -1;

  if ((fflush (msg->fp) == EOF) ||
      (fsync (fileno (msg->fp)) == -1))
  {
    mutt_perror _("Can't write message");
    return -1;
  }

  return 0;
}