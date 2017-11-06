void mutt_make_forward_subject (ENVELOPE *env, CONTEXT *ctx, HEADER *cur)
{
  char buffer[STRING];

  /* set the default subject for the message. */
  mutt_make_string (buffer, sizeof (buffer), NONULL(ForwFmt), ctx, cur);
  mutt_str_replace (&env->subject, buffer);
}