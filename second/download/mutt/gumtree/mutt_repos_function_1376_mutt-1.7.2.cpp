void mutt_merge_envelopes(ENVELOPE* base, ENVELOPE** extra)
{
  /* copies each existing element if necessary, and sets the element
  * to NULL in the source so that mutt_free_envelope doesn't leave us
  * with dangling pointers. */
#define MOVE_ELEM(h) if (!base->h) { base->h = (*extra)->h; (*extra)->h = NULL; }
  MOVE_ELEM(return_path);
  MOVE_ELEM(from);
  MOVE_ELEM(to);
  MOVE_ELEM(cc);
  MOVE_ELEM(bcc);
  MOVE_ELEM(sender);
  MOVE_ELEM(reply_to);
  MOVE_ELEM(mail_followup_to);
  MOVE_ELEM(list_post);
  MOVE_ELEM(message_id);
  MOVE_ELEM(supersedes);
  MOVE_ELEM(date);
  MOVE_ELEM(x_label);
  if (!base->refs_changed)
  {
    MOVE_ELEM(references);
  }
  if (!base->irt_changed)
  {
    MOVE_ELEM(in_reply_to);
  }
  
  /* real_subj is subordinate to subject */
  if (!base->subject)
  {
    base->subject = (*extra)->subject;
    base->real_subj = (*extra)->real_subj;
    (*extra)->subject = NULL;
    (*extra)->real_subj = NULL;
  }
  /* spam and user headers should never be hashed, and the new envelope may
    * have better values. Use new versions regardless. */
  mutt_buffer_free (&base->spam);
  mutt_free_list (&base->userhdrs);
  MOVE_ELEM(spam);
  MOVE_ELEM(userhdrs);
#undef MOVE_ELEM
  
  mutt_free_envelope(extra);
}