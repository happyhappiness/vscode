int  mutt_enter_string(char *buf, size_t buflen, int y, int x, int flags)
{
  int rv;
  ENTER_STATE *es = mutt_new_enter_state ();
  rv = _mutt_enter_string (buf, buflen, y, x, flags, 0, NULL, NULL, es);
  mutt_free_enter_state (&es);
  return rv;
}