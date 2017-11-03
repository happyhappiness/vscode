pid_t mutt_create_filter (const char *s, FILE **in, FILE **out, FILE **err)
{
  return (mutt_create_filter_fd (s, in, out, err, -1, -1, -1));
}