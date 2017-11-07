static void maildir_move_to_context(CONTEXT *ctx, struct maildir **md)
{
  maildir_add_to_context(ctx, *md);
  maildir_free_maildir(md);
}