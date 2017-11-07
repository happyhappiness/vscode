static int maildir_open_mailbox_append (CONTEXT *ctx, int flags)
{
  char tmp[_POSIX_PATH_MAX];

  if (flags & MUTT_APPENDNEW)
  {
    if (mkdir (ctx->path, S_IRWXU))
    {
      mutt_perror (ctx->path);
      return (-1);
    }

    snprintf (tmp, sizeof (tmp), "%s/cur", ctx->path);
    if (mkdir (tmp, S_IRWXU))
    {
      mutt_perror (tmp);
      rmdir (ctx->path);
      return (-1);
    }

    snprintf (tmp, sizeof (tmp), "%s/new", ctx->path);
    if (mkdir (tmp, S_IRWXU))
    {
      mutt_perror (tmp);
      snprintf (tmp, sizeof (tmp), "%s/cur", ctx->path);
      rmdir (tmp);
      rmdir (ctx->path);
      return (-1);
    }

    snprintf (tmp, sizeof (tmp), "%s/tmp", ctx->path);
    if (mkdir (tmp, S_IRWXU))
    {
      mutt_perror (tmp);
      snprintf (tmp, sizeof (tmp), "%s/cur", ctx->path);
      rmdir (tmp);
      snprintf (tmp, sizeof (tmp), "%s/new", ctx->path);
      rmdir (tmp);
      rmdir (ctx->path);
      return (-1);
    }
  }

  return 0;
}