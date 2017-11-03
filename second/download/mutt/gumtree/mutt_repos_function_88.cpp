void mutt_make_misc_reply_headers (ENVELOPE *env, CONTEXT *ctx,
				    HEADER *cur, ENVELOPE *curenv)
{
  /* This takes precedence over a subject that might have
   * been taken from a List-Post header.  Is that correct?
   */
  if (curenv->real_subj)
  {
    FREE (&env->subject);
    env->subject = safe_malloc (mutt_strlen (curenv->real_subj) + 5);
    sprintf (env->subject, "Re: %s", curenv->real_subj);	/* __SPRINTF_CHECKED__ */
  }
  else if (!env->subject)
    env->subject = safe_strdup ("Re: your mail");
}