static int flowed_maybe_quoted (char *cont)
{
  return regexec ((regex_t *) QuoteRegexp.rx, cont, 0, NULL, 0) == 0;
}