void mutt_buffer_addstr (BUFFER* buf, const char* s)
{
  mutt_buffer_add (buf, s, mutt_strlen (s));
}