static int link_threads (HEADER *parent, HEADER *child, CONTEXT *ctx)
{
  if (child == parent)
    return 0;

  mutt_break_thread (child);

  child->env->in_reply_to = mutt_new_list ();
  child->env->in_reply_to->data = safe_strdup (parent->env->message_id);
  
  mutt_set_flag (ctx, child, MUTT_TAG, 0);
  
  child->env->irt_changed = child->changed = 1;
  return 1;
}