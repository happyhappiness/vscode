  }
  else
    b = a;

  for (p = b->parts, count = 1; p; p = p->next, count++)
  {
    if (s->flags & MUTT_DISPLAY)
    {
      state_mark_attach (s);
      state_printf (s, _("[-- Attachment #%d"), count);
      if (p->description || p->filename || p->form_name)
      {
	state_puts (": ", s);
