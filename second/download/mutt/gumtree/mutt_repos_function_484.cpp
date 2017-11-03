void mutt_push_macro_event (int ch, int op)
{
  event_t tmp;

  tmp.ch = ch;
  tmp.op = op;

  if (MacroBufferCount >= MacroBufferLen)
    safe_realloc (&MacroEvents, (MacroBufferLen += 128) * sizeof(event_t));

  MacroEvents[MacroBufferCount++] = tmp;
}