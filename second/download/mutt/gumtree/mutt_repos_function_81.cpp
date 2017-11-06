static void make_from (ENVELOPE *hdr, char *buf, size_t len, int do_lists)
{
  int me;

  me = mutt_addr_is_user (hdr->from);

  if (do_lists || me)
  {
    if (check_for_mailing_list (hdr->to, "To ", buf, len))
      return;
    if (check_for_mailing_list (hdr->cc, "Cc ", buf, len))
      return;
  }

  if (me && hdr->to)
    snprintf (buf, len, "To %s", mutt_get_name (hdr->to));
  else if (me && hdr->cc)
    snprintf (buf, len, "Cc %s", mutt_get_name (hdr->cc));
  else if (me && hdr->bcc)
    snprintf (buf, len, "Bcc %s", mutt_get_name (hdr->bcc));
  else if (hdr->from)
    strfcpy (buf, mutt_get_name (hdr->from), len);
  else
    *buf = 0;
}