static void maildir_update_flags (CONTEXT *ctx, HEADER *o, HEADER *n)
{
  /* save the global state here so we can reset it at the
   * end of list block if required.
   */
  int context_changed = ctx->changed;
  
  /* user didn't modify this message.  alter the flags to match the
   * current state on disk.  This may not actually do
   * anything. mutt_set_flag() will just ignore the call if the status
   * bits are already properly set, but it is still faster not to pass
   * through it */
  if (o->flagged != n->flagged)
    mutt_set_flag (ctx, o, MUTT_FLAG, n->flagged);
  if (o->replied != n->replied)
    mutt_set_flag (ctx, o, MUTT_REPLIED, n->replied);
  if (o->read != n->read)
    mutt_set_flag (ctx, o, MUTT_READ, n->read);
  if (o->old != n->old)
    mutt_set_flag (ctx, o, MUTT_OLD, n->old);

  /* mutt_set_flag() will set this, but we don't need to
   * sync the changes we made because we just updated the
   * context to match the current on-disk state of the
   * message.
   */
  o->changed = 0;
  
  /* if the mailbox was not modified before we made these
   * changes, unset the changed flag since nothing needs to
   * be synchronized.
   */
  if (!context_changed)
    ctx->changed = 0;
}