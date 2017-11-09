void smime_getkeys (ENVELOPE *env)
{
  ADDRESS *t;
  int found = 0;

  if (option (OPTSDEFAULTDECRYPTKEY) && SmimeDefaultKey && *SmimeDefaultKey)
  {
    snprintf (SmimeKeyToUse, sizeof (SmimeKeyToUse), "%s/%s", 
	      NONULL (SmimeKeys), SmimeDefaultKey);
    
    snprintf (SmimeCertToUse, sizeof (SmimeCertToUse), "%s/%s",
	      NONULL(SmimeCertificates), SmimeDefaultKey);

    return;
  }

  for (t = env->to; !found && t; t = t->next)
    if (mutt_addr_is_user (t))
    {
      found = 1;
      _smime_getkeys (t->mailbox);
    }
  for (t = env->cc; !found && t; t = t->next)
    if (mutt_addr_is_user (t))
    {
      found = 1;
      _smime_getkeys (t->mailbox);
    }
  if (!found && (t = mutt_default_from()))
  {
    _smime_getkeys (t->mailbox);
    rfc822_free_address (&t);
  }
}