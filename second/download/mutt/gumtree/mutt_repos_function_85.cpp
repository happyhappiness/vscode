LIST *mutt_make_references(ENVELOPE *e)
{
  LIST *t = NULL, *l = NULL;

  if (e->references)
    l = mutt_copy_list (e->references);
  else
    l = mutt_copy_list (e->in_reply_to);
  
  if (e->message_id)
  {
    t = mutt_new_list();
    t->data = safe_strdup(e->message_id);
    t->next = l;
    l = t;
  }
  
  return l;
}