void mutt_make_misc_reply_headers (ENVELOPE *env, CONTEXT *ctx,
				    HEADER *cur, ENVELOPE *curenv)
{
  if (curenv->real_subj)
  {
    env->subject = safe_malloc (mutt_strlen (curenv->real_subj) + 5);
    sprintf (env->subject, "Re: %s", curenv->real_subj);	/* __SPRINTF_CHECKED__ */
  }
  else
    env->subject = safe_strdup ("Re: your mail");
  
}