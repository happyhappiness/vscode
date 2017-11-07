void mbox_reset_atime (CONTEXT *ctx, struct stat *st)
{
  struct utimbuf utimebuf;
  struct stat _st;

  if (!st)
  {
    if (stat (ctx->path, &_st) < 0)
      return;
    st = &_st;
  }

  utimebuf.actime = st->st_atime;
  utimebuf.modtime = st->st_mtime;

  /*
   * When $mbox_check_recent is set, existing new mail is ignored, so do not
   * reset the atime to mtime-1 to signal new mail.
   */
  if (!option(OPTMAILCHECKRECENT) && utimebuf.actime >= utimebuf.modtime && mbox_has_new(ctx))
    utimebuf.actime = utimebuf.modtime - 1;

  utime (ctx->path, &utimebuf);
}