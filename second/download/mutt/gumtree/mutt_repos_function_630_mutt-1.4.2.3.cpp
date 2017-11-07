static void enriched_puts (char *s, struct enriched_state *stte)
{
  char *c;

  if (stte->buff_len < stte->buff_used + mutt_strlen(s))
  {
    stte->buff_len += LONG_STRING;
    safe_realloc ((void **) &stte->buffer, stte->buff_len + 1);
  }
  c = s;
  while (*c)
  {
    stte->buffer[stte->buff_used++] = *c;
    c++;
  }
}