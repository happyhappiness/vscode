  
  return rv;
}

void state_mark_attach (STATE *s)
{
  if ((s->flags & MUTT_DISPLAY) && !mutt_strcmp (Pager, "builtin"))
    state_puts (AttachmentMarker, s);
}

void state_attach_puts (const char *t, STATE *s)
{
  if (*t != '\n') state_mark_attach (s);
