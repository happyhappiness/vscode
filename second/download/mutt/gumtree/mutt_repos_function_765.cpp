static int verify_sender (HEADER *h, gpgme_protocol_t protocol)
{
  ADDRESS *sender = NULL;
  unsigned int ret = 1;

  if (h->env->from)
    {
      h->env->from = mutt_expand_aliases (h->env->from);
      sender = h->env->from;
    }
  else if (h->env->sender)
    {
      h->env->sender = mutt_expand_aliases (h->env->sender);
      sender = h->env->sender;
    }

  if (sender)
  {
    if (signature_key)
    {
      gpgme_key_t key = signature_key;
      gpgme_user_id_t uid = NULL;
      int sender_length = 0;
      int uid_length = 0;

      sender_length = strlen (sender->mailbox);
      for (uid = key->uids; uid && ret; uid = uid->next)
      {
	uid_length = strlen (uid->email);
	if (1
	    && (uid->email[0] == '<')
	    && (uid->email[uid_length - 1] == '>')
	    && (uid_length == sender_length + 2))
	{
	  const char* at_sign = strchr(uid->email + 1, '@');
	  if (at_sign == NULL)
	  {
	    if (! strncmp (uid->email + 1, sender->mailbox, sender_length))
	      ret = 0;
	  }
	  else
	  {
	    /*
	     * Assume address is 'mailbox@domainname'.
	     * The mailbox part is case-sensitive,
	     * the domainname is not. (RFC 2821)
	     */
	    const char* tmp_email = uid->email + 1;
	    const char* tmp_sender = sender->mailbox;
	    /* length of mailbox part including '@' */
	    int mailbox_length = at_sign - tmp_email + 1;
	    int domainname_length = sender_length - mailbox_length;
	    int mailbox_match, domainname_match;

	    mailbox_match = (! strncmp (tmp_email, tmp_sender,
		mailbox_length));
	    tmp_email += mailbox_length;
	    tmp_sender += mailbox_length;
	    domainname_match = (! strncasecmp (tmp_email, tmp_sender,
		domainname_length));
	    if (mailbox_match && domainname_match)
	      ret = 0;
	  }
	}
      }
    }
    else
      mutt_any_key_to_continue (_("Failed to verify sender"));
  }
  else
    mutt_any_key_to_continue (_("Failed to figure out sender"));

  if (signature_key)
  {
    gpgme_key_unref (signature_key);
    signature_key = NULL;
  }

  return ret;
}