void mutt_free_envelope (ENVELOPE **p)
{
  if (!*p) return;
  rfc822_free_address (&(*p)->return_path);
  rfc822_free_address (&(*p)->from);
  rfc822_free_address (&(*p)->to);
  rfc822_free_address (&(*p)->cc);
  rfc822_free_address (&(*p)->bcc);
  rfc822_free_address (&(*p)->sender);
  rfc822_free_address (&(*p)->reply_to);
  rfc822_free_address (&(*p)->mail_followup_to);

  FREE (&(*p)->list_post);
  FREE (&(*p)->subject);
  /* real_subj is just an offset to subject and shouldn't be freed */
  FREE (&(*p)->disp_subj);
  FREE (&(*p)->message_id);
  FREE (&(*p)->supersedes);
  FREE (&(*p)->date);
  FREE (&(*p)->x_label);

  mutt_buffer_free (&(*p)->spam);

  mutt_free_list (&(*p)->references);
  mutt_free_list (&(*p)->in_reply_to);
  mutt_free_list (&(*p)->userhdrs);
  FREE (p);		/* __FREE_CHECKED__ */
}