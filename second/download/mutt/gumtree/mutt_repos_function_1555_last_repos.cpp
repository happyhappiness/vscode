static void maildir_update_mtime (CONTEXT * ctx)
{
  char buf[_POSIX_PATH_MAX];
  struct stat st;
  struct mh_data *data = mh_data (ctx);

  if (ctx->magic == MUTT_MAILDIR)
  {
    snprintf (buf, sizeof (buf), "%s/%s", ctx->path, "cur");
    if (stat (buf, &st) == 0)
      data->mtime_cur = st.st_mtime;
    snprintf (buf, sizeof (buf), "%s/%s", ctx->path, "new");
  }
  else
  {
    snprintf (buf, sizeof (buf), "%s/.mh_sequences", ctx->path);
    if (stat (buf, &st) == 0)
      data->mtime_cur = st.st_mtime;

    strfcpy (buf, ctx->path, sizeof (buf));
  }

  if (stat (buf, &st) == 0)
    ctx->mtime = st.st_mtime;
}