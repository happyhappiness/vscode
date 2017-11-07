static const char *
parse_quote (const char *s, char *token, size_t *tokenlen, size_t tokenmax)
{
  if (*tokenlen < tokenmax)
    token[(*tokenlen)++] = '"';
  while (*s)
  {
    if (*tokenlen < tokenmax)
      token[*tokenlen] = *s;
    if (*s == '"')
    {
      (*tokenlen)++;
      return (s + 1);
    }
    if (*s == '\\')
    {
      if (!*++s)
	break;

      if (*tokenlen < tokenmax)
	token[*tokenlen] = *s;
    }
    (*tokenlen)++;
    s++;
  }
  RFC822Error = ERR_MISMATCH_QUOTE;
  return NULL;
}