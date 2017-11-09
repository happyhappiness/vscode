static int mx_open_mailbox_append (CONTEXT *ctx, int flags)
{
  struct stat sb;

  ctx->append = 1;
  ctx->magic = mx_get_magic (ctx->path);
  if (ctx->magic == 0)
  {
    mutt_error (_("%s is not a mailbox."), ctx->path);
    return -1;
  }

  if (ctx->magic < 0)
  {
    if (stat (ctx->path, &sb) == -1)
    {
      if (errno == ENOENT)
      {
#ifdef USE_COMPRESSED
        if (mutt_comp_can_append (ctx))
          ctx->magic = MUTT_COMPRESSED;
        else
#endif
          ctx->magic = DefaultMagic;
        flags |= MUTT_APPENDNEW;
      }
      else
      {
        mutt_perror (ctx->path);
        return -1;
      }
    }
    else
      return -1;
  }

  ctx->mx_ops = mx_get_ops (ctx->magic);
  if (!ctx->mx_ops || !ctx->mx_ops->open_append)
    return -1;

  return ctx->mx_ops->open_append (ctx, flags);
}