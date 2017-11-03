static void clean_references (THREAD *brk, THREAD *cur)
{
  THREAD *p;
  LIST *ref = NULL;
  int done = 0;

  for (; cur; cur = cur->next, done = 0)
  {
    /* parse subthread recursively */
    clean_references (brk, cur->child);

    if (!cur->message)
      break; /* skip pseudo-message */

    /* Looking for the first bad reference according to the new threading.
     * Optimal since Mutt stores the references in reverse order, and the
     * first loop should match immediately for mails respecting RFC2822. */
    for (p = brk; !done && p; p = p->parent)
      for (ref = cur->message->env->references; p->message && ref; ref = ref->next)
	if (!mutt_strcasecmp (ref->data, p->message->env->message_id))
	{
	  done = 1;
	  break;
	}

    if (done)
    {
      HEADER *h = cur->message;

      /* clearing the References: header from obsolete Message-ID(s) */
      mutt_free_list (&ref->next);

      h->env->refs_changed = h->changed = 1;
    }
  }
}