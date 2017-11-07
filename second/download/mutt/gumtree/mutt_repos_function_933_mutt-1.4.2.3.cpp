void mutt_free_envelope (ENVELOPE **p)
{
  if (!*p) return;
  rfc822_free_address (&(*p)->return_path);
  rfc822_free_address (&(*p)->to);
  rfc822_free_address (&(*p)->cc);
  rfc822_free_address (&(*p)->bcc);
  rfc822_free_address (&(*p)->sender);
  rfc822_free_address (&(*p)->from);
  rfc822_free_address (&(*p)->reply_to);
  rfc822_free_address (&(*p)->mail_followup_to);
  safe_free ((void **) &(*p)->subject);
  safe_free ((void **) &(*p)->message_id);
  safe_free ((void **) &(*p)->supersedes);
  safe_free ((void **) &(*p)->date);
  mutt_free_list (&(*p)->references);
  mutt_free_list (&(*p)->in_reply_to);
  mutt_free_list (&(*p)->userhdrs);
  safe_free ((void **) p);
}