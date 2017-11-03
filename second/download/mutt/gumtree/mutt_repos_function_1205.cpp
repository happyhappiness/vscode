static void check_subjects (CONTEXT *ctx, int init)
{
  HEADER *cur;
  THREAD *tmp;
  int i;

  for (i = 0; i < ctx->msgcount; i++)
  {
    cur = ctx->hdrs[i];
    if (cur->thread->check_subject)
      cur->thread->check_subject = 0;
    else if (!init)
      continue;

    /* figure out which messages have subjects different than their parents' */
    tmp = cur->thread->parent;
    while (tmp && !tmp->message)
    {
      tmp = tmp->parent;
    }

    if (!tmp)
      cur->subject_changed = 1;
    else if (cur->env->real_subj && tmp->message->env->real_subj)
      cur->subject_changed = mutt_strcmp (cur->env->real_subj,
					  tmp->message->env->real_subj) ? 1 : 0;
    else
      cur->subject_changed = (cur->env->real_subj
			      || tmp->message->env->real_subj) ? 1 : 0;
  }
}