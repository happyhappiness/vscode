static int mh_open_mailbox_append (CONTEXT *ctx, int flags)
{
  char tmp[_POSIX_PATH_MAX];
  int i;

  if (flags & MUTT_APPENDNEW)
  {
    if (mkdir (ctx->path, S_IRWXU))
    {
      mutt_perror (ctx->path);
      return (-1);
    }

    snprintf (tmp, sizeof (tmp), "%s/.mh_sequences", ctx->path);
    if ((i = creat (tmp, S_IRWXU)) == -1)
    {
      mutt_perror (tmp);
      rmdir (ctx->path);
      return (-1);
    }
    close (i);
  }

  return 0;
}