void mutt_fix_reply_recipients (ENVELOPE *env)
{
  if (! option (OPTMETOO))
  {
    /* the order is important here.  do the CC: first so that if the
     * the user is the only recipient, it ends up on the TO: field
     */
    env->cc = remove_user (env->cc, (env->to == NULL));
    env->to = remove_user (env->to, (env->cc == NULL));
  }
  
  /* the CC field can get cluttered, especially with lists */
  env->to = mutt_remove_duplicates (env->to);
  env->cc = mutt_remove_duplicates (env->cc);
  env->cc = mutt_remove_xrefs (env->to, env->cc);
  
  if (env->cc && !env->to)
  {
    env->to = env->cc;
    env->cc = NULL;
  }
}