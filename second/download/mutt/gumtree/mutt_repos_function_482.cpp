void mutt_unget_event (int ch, int op)
{
  event_t tmp;

  tmp.ch = ch;
  tmp.op = op;

  if (UngetCount >= UngetLen)
    safe_realloc (&UngetKeyEvents, (UngetLen += 16) * sizeof(event_t));

  UngetKeyEvents[UngetCount++] = tmp;
}