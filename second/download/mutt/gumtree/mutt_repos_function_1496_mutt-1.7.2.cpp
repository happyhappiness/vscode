static int maildir_move_to_context (CONTEXT * ctx, struct maildir **md)
{
  int r;
  r = maildir_add_to_context (ctx, *md);
  maildir_free_maildir (md);
  return r;
}