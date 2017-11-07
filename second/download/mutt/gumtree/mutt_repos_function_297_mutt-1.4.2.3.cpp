void mutt_ungetch (int ch, int op)
{
  event_t tmp;

  tmp.ch = ch;
  tmp.op = op;

  if (UngetCount >= UngetBufLen)
    safe_realloc ((void **) &KeyEvent, (UngetBufLen += 128) * sizeof(event_t));

  KeyEvent[UngetCount++] = tmp;
}