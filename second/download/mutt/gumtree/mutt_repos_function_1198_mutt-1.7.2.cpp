static THREAD *find_subject (CONTEXT *ctx, THREAD *cur)
{
  struct hash_elem *ptr;
  THREAD *tmp, *last = NULL;
  unsigned int hash;
  LIST *subjects = NULL, *oldlist;
  time_t date = 0;  

  subjects = make_subject_list (cur, &date);

  while (subjects)
  {
    hash = ctx->subj_hash->hash_string ((unsigned char *) subjects->data,
					ctx->subj_hash->nelem);
    for (ptr = ctx->subj_hash->table[hash]; ptr; ptr = ptr->next)
    {
      tmp = ((HEADER *) ptr->data)->thread;
      if (tmp != cur &&			   /* don't match the same message */
	  !tmp->fake_thread &&		   /* don't match pseudo threads */
	  tmp->message->subject_changed && /* only match interesting replies */
	  !is_descendant (tmp, cur) &&	   /* don't match in the same thread */
	  (date >= (option (OPTTHREADRECEIVED) ?
		    tmp->message->received :
		    tmp->message->date_sent)) &&
	  (!last ||
	   (option (OPTTHREADRECEIVED) ?
	    (last->message->received < tmp->message->received) :
	    (last->message->date_sent < tmp->message->date_sent))) &&
	  tmp->message->env->real_subj &&
	  mutt_strcmp (subjects->data, tmp->message->env->real_subj) == 0)
	last = tmp; /* best match so far */
    }

    oldlist = subjects;
    subjects = subjects->next;
    FREE (&oldlist);
  }
  return (last);
}