int mh_read_dir (CONTEXT *ctx, const char *subdir)
{
  struct maildir *md;
  struct mh_sequences mhs;
  struct maildir **last;
  int count;
  
  md = NULL;
  last = &md;
  count = 0;

  memset (&mhs, 0, sizeof (mhs));
  
  maildir_update_mtime(ctx);

  if(maildir_parse_dir(ctx, &last, subdir, &count) == -1)
    return -1;

  if (ctx->magic == M_MH)
  {
    mh_read_sequences (&mhs, ctx->path);
    mh_update_maildir (md, &mhs);
    mhs_free_sequences (&mhs);
  }
  
  maildir_move_to_context(ctx, &md);
  return 0;
}