static LIST *make_subject_list (THREAD *cur, time_t *dateptr)
{
  THREAD *start = cur;
  ENVELOPE *env;
  time_t thisdate;
  LIST *curlist, *oldlist, *newlist, *subjects = NULL;
  int rc = 0;
  
  FOREVER
  {
    while (!cur->message)
      cur = cur->child;

    if (dateptr)
    {
      thisdate = option (OPTTHREADRECEIVED)
	? cur->message->received : cur->message->date_sent;
      if (!*dateptr || thisdate < *dateptr)
	*dateptr = thisdate;
    }

    env = cur->message->env;
    if (env->real_subj &&
	((env->real_subj != env->subject) || (!option (OPTSORTRE))))
    {
      for (curlist = subjects, oldlist = NULL;
	   curlist; oldlist = curlist, curlist = curlist->next)
      {
	rc = mutt_strcmp (env->real_subj, curlist->data);
	if (rc >= 0)
	  break;
      }
      if (!curlist || rc > 0)
      {
	newlist = safe_calloc (1, sizeof (LIST));
	newlist->data = env->real_subj;
	if (oldlist)
	{
	  newlist->next = oldlist->next;
	  oldlist->next = newlist;
	}
	else
	{
	  newlist->next = subjects;
	  subjects = newlist;
	}
      }
    }

    while (!cur->next && cur != start)
    {
      cur = cur->parent;
    }
    if (cur == start)
      break;
    cur = cur->next;
  }

  return (subjects);
}