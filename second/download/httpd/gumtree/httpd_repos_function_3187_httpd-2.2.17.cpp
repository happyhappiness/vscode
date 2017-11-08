static int PTRCALL
sb_charMatches(const ENCODING *enc, const char *p, int c)
{
  return *p == c;
}