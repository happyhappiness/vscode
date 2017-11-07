ADDRESS *mutt_get_address (ENVELOPE *env, char **pfxp)
{
  ADDRESS *adr;
  char *pfx = NULL;

  if (mutt_addr_is_user (env->from))
  {
    if (env->to && !mutt_is_mail_list (env->to))
    {
      pfx = "To";
      adr = env->to;
    }
    else
    {
      pfx = "Cc";
      adr = env->cc;
    }
  }
  else if (env->reply_to && !mutt_is_mail_list (env->reply_to))
  {
    pfx = "Reply-To";
    adr = env->reply_to;
  }
  else
  {
    adr = env->from;
    pfx = "From";
  }

  if (pfxp) *pfxp = pfx;

  return adr;
}