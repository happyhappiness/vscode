static void maildir_update_mtime(CONTEXT *ctx)
{
  char buf[_POSIX_PATH_MAX];
  struct stat st;
  
  if(ctx->magic == M_MAILDIR)
  {
    snprintf(buf, sizeof(buf), "%s/%s", ctx->path, "cur");
    if(stat (buf, &st) == 0)
      ctx->mtime_cur = st.st_mtime;
    snprintf(buf, sizeof(buf), "%s/%s", ctx->path, "new");
  }
  else
  {
    snprintf (buf, sizeof (buf), "%s/.mh_sequences", ctx->path);
    if (stat (buf, &st) == 0)
      ctx->mtime_cur = st.st_mtime;
    
    strfcpy(buf, ctx->path, sizeof(buf));
  }
  
  if(stat(buf, &st) == 0)
    ctx->mtime = st.st_mtime;
}