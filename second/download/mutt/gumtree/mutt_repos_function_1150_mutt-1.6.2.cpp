int mutt_user_is_recipient (HEADER *h)
{
  ENVELOPE *env = h->env;

  if(!h->recip_valid)
  {
    h->recip_valid = 1;
    
    if (mutt_addr_is_user (env->from))
      h->recipient = 4;
    else if (user_in_addr (env->to))
    {
      if (env->to->next || env->cc)
	h->recipient = 2; /* non-unique recipient */
      else
	h->recipient = 1; /* unique recipient */
    }
    else if (user_in_addr (env->cc))
      h->recipient = 3;
    else if (check_for_mailing_list (env->to, NULL, NULL, 0))
      h->recipient = 5;
    else if (check_for_mailing_list (env->cc, NULL, NULL, 0))
      h->recipient = 5;
    else
      h->recipient = 0;
  }
  
  return h->recipient;
}