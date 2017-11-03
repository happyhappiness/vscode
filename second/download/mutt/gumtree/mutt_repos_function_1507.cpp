static int mh_read_dir (CONTEXT * ctx, const char *subdir)
{
  struct maildir *md;
  struct mh_sequences mhs;
  struct maildir **last;
  struct mh_data *data;
  int count;
  char msgbuf[STRING];
  progress_t progress;

  memset (&mhs, 0, sizeof (mhs));
  if (!ctx->quiet)
  {
    snprintf (msgbuf, sizeof (msgbuf), _("Scanning %s..."), ctx->path);
    mutt_progress_init (&progress, msgbuf, MUTT_PROGRESS_MSG, ReadInc, 0);
  }

  if (!ctx->data)
  {
    ctx->data = safe_calloc(sizeof (struct mh_data), 1);
  }
  data = mh_data (ctx);

  maildir_update_mtime (ctx);

  md = NULL;
  last = &md;
  count = 0;
  if (maildir_parse_dir (ctx, &last, subdir, &count, &progress) == -1)
    return -1;

  if (!ctx->quiet)
  {
    snprintf (msgbuf, sizeof (msgbuf), _("Reading %s..."), ctx->path);
    mutt_progress_init (&progress, msgbuf, MUTT_PROGRESS_MSG, ReadInc, count);
  }
  maildir_delayed_parsing (ctx, &md, &progress);

  if (ctx->magic == MUTT_MH)
  {
    if (mh_read_sequences (&mhs, ctx->path) < 0)
    {
      maildir_free_maildir (&md);
      return -1;
    }
    mh_update_maildir (md, &mhs);
    mhs_free_sequences (&mhs);
  }

  maildir_move_to_context (ctx, &md);

  if (!data->mh_umask)
    data->mh_umask = mh_umask (ctx);

  return 0;
}