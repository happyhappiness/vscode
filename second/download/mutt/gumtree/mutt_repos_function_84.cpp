int mutt_fetch_recips (ENVELOPE *out, ENVELOPE *in, int flags)
{
  char prompt[STRING];
  ADDRESS *tmp;
  int hmfupto = -1;

  if ((flags & (SENDLISTREPLY|SENDGROUPREPLY)) && in->mail_followup_to)
  {
    snprintf (prompt, sizeof (prompt), _("Follow-up to %s%s?"),
	      in->mail_followup_to->mailbox,
	      in->mail_followup_to->next ? ",..." : "");

    if ((hmfupto = query_quadoption (OPT_MFUPTO, prompt)) == -1)
      return -1;
  }

  if (flags & SENDLISTREPLY)
  {
    tmp = find_mailing_lists (in->to, in->cc);
    rfc822_append (&out->to, tmp, 0);
    rfc822_free_address (&tmp);

    if (in->mail_followup_to && hmfupto == MUTT_YES &&
        default_to (&out->cc, in, flags & SENDLISTREPLY, hmfupto) == -1)
      return (-1); /* abort */
  }
  else
  {
    if (default_to (&out->to, in, flags & SENDGROUPREPLY, hmfupto) == -1)
      return (-1); /* abort */

    if ((flags & SENDGROUPREPLY) && (!in->mail_followup_to || hmfupto != MUTT_YES))
    {
      /* if(!mutt_addr_is_user(in->to)) */
      rfc822_append (&out->cc, in->to, 1);
      rfc822_append (&out->cc, in->cc, 1);
    }
  }
  return 0;
}