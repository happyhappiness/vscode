static int default_to (ADDRESS **to, ENVELOPE *env, int flags, int hmfupto)
{
  char prompt[STRING];

  if (flags && env->mail_followup_to && hmfupto == MUTT_YES) 
  {
    rfc822_append (to, env->mail_followup_to, 1);
    return 0;
  }

  /* Exit now if we're setting up the default Cc list for list-reply
   * (only set if Mail-Followup-To is present and honoured).
   */
  if (flags & SENDLISTREPLY)
    return 0;

  if (!option(OPTREPLYSELF) && mutt_addr_is_user (env->from))
  {
    /* mail is from the user, assume replying to recipients */
    rfc822_append (to, env->to, 1);
  }
  else if (env->reply_to)
  {
    if ((mutt_addrcmp (env->from, env->reply_to) && !env->reply_to->next) || 
	(option (OPTIGNORELISTREPLYTO) &&
	mutt_is_mail_list (env->reply_to) &&
	(mutt_addrsrc (env->reply_to, env->to) ||
	mutt_addrsrc (env->reply_to, env->cc))))
    {
      /* If the Reply-To: address is a mailing list, assume that it was
       * put there by the mailing list, and use the From: address
       * 
       * We also take the from header if our correspondent has a reply-to
       * header which is identical to the electronic mail address given
       * in his From header.
       * 
       */
      rfc822_append (to, env->from, 0);
    }
    else if (!(mutt_addrcmp (env->from, env->reply_to) && 
	       !env->reply_to->next) &&
	     quadoption (OPT_REPLYTO) != MUTT_YES)
    {
      /* There are quite a few mailing lists which set the Reply-To:
       * header field to the list address, which makes it quite impossible
       * to send a message to only the sender of the message.  This
       * provides a way to do that.
       */
      /* L10N:
         Asks whether the user respects the reply-to header.
         If she says no, mutt will reply to the from header's address instead. */
      snprintf (prompt, sizeof (prompt), _("Reply to %s%s?"),
		env->reply_to->mailbox, 
		env->reply_to->next?",...":"");
      switch (query_quadoption (OPT_REPLYTO, prompt))
      {
      case MUTT_YES:
	rfc822_append (to, env->reply_to, 0);
	break;

      case MUTT_NO:
	rfc822_append (to, env->from, 0);
	break;

      default:
	return (-1); /* abort */
      }
    }
    else
      rfc822_append (to, env->reply_to, 0);
  }
  else
    rfc822_append (to, env->from, 0);

  return (0);
}