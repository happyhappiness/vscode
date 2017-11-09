void state_mark_attach (STATE *s)
{
  if ((s->flags & MUTT_DISPLAY) && !mutt_strcmp (Pager, "builtin"))
    state_puts (AttachmentMarker, s);
}