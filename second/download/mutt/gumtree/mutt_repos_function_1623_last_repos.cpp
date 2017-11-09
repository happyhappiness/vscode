static int
setup_paths (CONTEXT *ctx)
{
  if (!ctx)
    return -1;

  char tmppath[_POSIX_PATH_MAX];
  FILE *tmpfp;

  /* Setup the right paths */
  FREE(&ctx->realpath);
  ctx->realpath = ctx->path;

  /* We will uncompress to /tmp */
  mutt_mktemp (tmppath, sizeof (tmppath));
  ctx->path = safe_strdup (tmppath);

  if ((tmpfp = safe_fopen (ctx->path, "w")) == NULL)
    return -1;

  safe_fclose (&tmpfp);
  return 0;
}