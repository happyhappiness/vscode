int mix_check_message (HEADER *msg)
{
  const char *fqdn;
  short need_hostname = 0;
  ADDRESS *p;
  
  if (msg->env->cc || msg->env->bcc)
  {
    mutt_error _("Mixmaster doesn't accept Cc or Bcc headers.");
    return -1;
  }

  /* When using mixmaster, we MUST qualify any addresses since
   * the message will be delivered through remote systems.
   * 
   * use_domain won't be respected at this point, hidden_host will.
   */

  for (p = msg->env->to; p; p = p->next)
  {
    if (!p->group && strchr (p->mailbox, '@') == NULL)
    {
      need_hostname = 1;
      break;
    }
  }
    
  if (need_hostname)
  {
    
    if (!(fqdn = mutt_fqdn (1)))
    {
      mutt_error _("Please set the hostname variable to a proper value when using mixmaster!");
      return (-1);
    }
  
    /* Cc and Bcc are empty at this point. */
    rfc822_qualify (msg->env->to, fqdn);
    rfc822_qualify (msg->env->reply_to, fqdn);
    rfc822_qualify (msg->env->mail_followup_to, fqdn);
  }

  return 0;
}