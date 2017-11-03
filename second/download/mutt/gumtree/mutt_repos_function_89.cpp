void mutt_add_to_reference_headers (ENVELOPE *env, ENVELOPE *curenv, LIST ***pp, LIST ***qq)
{
  LIST **p = NULL, **q = NULL;

  if (pp) p = *pp;
  if (qq) q = *qq;
  
  if (!p) p = &env->references;
  if (!q) q = &env->in_reply_to;
  
  while (*p) p = &(*p)->next;
  while (*q) q = &(*q)->next;
  
  *p = mutt_make_references (curenv);
  
  if (curenv->message_id)
  {
    *q = mutt_new_list();
    (*q)->data = safe_strdup (curenv->message_id);
  }
  
  if (pp) *pp = p;
  if (qq) *qq = q;
  
}