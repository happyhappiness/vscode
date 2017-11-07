static void
restore_envelope(ENVELOPE * e, const unsigned char *d, int *off, int convert)
{
  int real_subj_off;

  restore_address(&e->return_path, d, off, convert);
  restore_address(&e->from, d, off, convert);
  restore_address(&e->to, d, off, convert);
  restore_address(&e->cc, d, off, convert);
  restore_address(&e->bcc, d, off, convert);
  restore_address(&e->sender, d, off, convert);
  restore_address(&e->reply_to, d, off, convert);
  restore_address(&e->mail_followup_to, d, off, convert);

  restore_char(&e->list_post, d, off, convert);
  restore_char(&e->subject, d, off, convert);
  restore_int((unsigned int *) (&real_subj_off), d, off);

  if (0 <= real_subj_off)
    e->real_subj = e->subject + real_subj_off;
  else
    e->real_subj = NULL;

  restore_char(&e->message_id, d, off, 0);
  restore_char(&e->supersedes, d, off, 0);
  restore_char(&e->date, d, off, 0);
  restore_char(&e->x_label, d, off, convert);

  restore_buffer(&e->spam, d, off, convert);

  restore_list(&e->references, d, off, 0);
  restore_list(&e->in_reply_to, d, off, 0);
  restore_list(&e->userhdrs, d, off, convert);
}