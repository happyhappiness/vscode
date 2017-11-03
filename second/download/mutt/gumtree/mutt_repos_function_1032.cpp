static unsigned char *
dump_envelope(ENVELOPE * e, unsigned char *d, int *off, int convert)
{
  d = dump_address(e->return_path, d, off, convert);
  d = dump_address(e->from, d, off, convert);
  d = dump_address(e->to, d, off, convert);
  d = dump_address(e->cc, d, off, convert);
  d = dump_address(e->bcc, d, off, convert);
  d = dump_address(e->sender, d, off, convert);
  d = dump_address(e->reply_to, d, off, convert);
  d = dump_address(e->mail_followup_to, d, off, convert);

  d = dump_char(e->list_post, d, off, convert);
  d = dump_char(e->subject, d, off, convert);

  if (e->real_subj)
    d = dump_int(e->real_subj - e->subject, d, off);
  else
    d = dump_int(-1, d, off);

  d = dump_char(e->message_id, d, off, 0);
  d = dump_char(e->supersedes, d, off, 0);
  d = dump_char(e->date, d, off, 0);
  d = dump_char(e->x_label, d, off, convert);

  d = dump_buffer(e->spam, d, off, convert);

  d = dump_list(e->references, d, off, 0);
  d = dump_list(e->in_reply_to, d, off, 0);
  d = dump_list(e->userhdrs, d, off, convert);

  return d;
}