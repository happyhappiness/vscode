void mutt_expand_aliases_env (ENVELOPE *env)
{
  env->from = mutt_expand_aliases (env->from);
  env->to = mutt_expand_aliases (env->to);
  env->cc = mutt_expand_aliases (env->cc);
  env->bcc = mutt_expand_aliases (env->bcc);
  env->reply_to = mutt_expand_aliases (env->reply_to);
  env->mail_followup_to = mutt_expand_aliases (env->mail_followup_to);
}