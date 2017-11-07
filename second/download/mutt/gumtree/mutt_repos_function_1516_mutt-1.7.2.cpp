static int maildir_mh_open_message (CONTEXT *ctx, MESSAGE *msg, int msgno,
                                    int is_maildir)
{
  HEADER *cur = ctx->hdrs[msgno];
  char path[_POSIX_PATH_MAX];

  snprintf (path, sizeof (path), "%s/%s", ctx->path, cur->path);

  msg->fp = fopen (path, "r");
  if (msg->fp == NULL && errno == ENOENT && is_maildir)
    msg->fp = maildir_open_find_message (ctx->path, cur->path);

  if (!msg->fp)
  {
    mutt_perror (path);
    dprint (1, (debugfile, "maildir_mh_open_message: fopen: %s: %s (errno %d).\n",
            path, strerror (errno), errno));
    return -1;
  }

  return 0;
}