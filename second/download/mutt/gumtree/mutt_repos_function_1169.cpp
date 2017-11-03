static void make_from_addr (ENVELOPE *hdr, char *buf, size_t len, int do_lists)
{
  int me;

  me = mutt_addr_is_user (hdr->from);

  if (do_lists || me)
  {
    if (check_for_mailing_list_addr (hdr->to, buf, len))
      return;
    if (check_for_mailing_list_addr (hdr->cc, buf, len))
      return;
  }

  if (me && hdr->to)
    snprintf (buf, len, "%s", hdr->to->mailbox);
  else if (me && hdr->cc)
    snprintf (buf, len, "%s", hdr->cc->mailbox);
  else if (hdr->from)
    strfcpy (buf, hdr->from->mailbox, len);
  else
    *buf = 0;
}