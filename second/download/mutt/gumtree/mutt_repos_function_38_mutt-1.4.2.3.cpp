int mutt_fetch_recips (ENVELOPE *out, ENVELOPE *in, int flags)
{
  ADDRESS *tmp;
  if (flags & SENDLISTREPLY)
  {
    tmp = find_mailing_lists (in->to, in->cc);
    rfc822_append (&out->to, tmp);
    rfc822_free_address (&tmp);

    if (in->mail_followup_to &&
        default_to (&out->cc, in, flags & SENDLISTREPLY) == -1)
      return (-1); /* abort */
  }
  else
  {
    if (default_to (&out->to, in, flags & SENDGROUPREPLY) == -1)
      return (-1); /* abort */

    if ((flags & SENDGROUPREPLY) && !in->mail_followup_to)
    {
      /* if(!mutt_addr_is_user(in->to)) */
      rfc822_append (&out->cc, in->to);
      rfc822_append (&out->cc, in->cc);
    }
  }
  return 0;
}