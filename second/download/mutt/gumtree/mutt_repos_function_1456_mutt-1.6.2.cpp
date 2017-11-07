static inline mode_t mh_umask (CONTEXT* ctx)
{
  struct stat st;
  struct mh_data* data = mh_data (ctx);

  if (data && data->mh_umask)
    return data->mh_umask;

  if (stat (ctx->path, &st))
  {
    dprint (1, (debugfile, "stat failed on %s\n", ctx->path));
    return 077;
  }

  return 0777 & ~st.st_mode;
}