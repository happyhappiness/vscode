static int parse_fkey(char *s)
{
  char *t;
  int n = 0;

  if(s[0] != '<' || ascii_tolower(s[1]) != 'f')
    return -1;

  for(t = s + 2; *t && isdigit((unsigned char) *t); t++)
  {
    n *= 10;
    n += *t - '0';
  }

  if(*t != '>')
    return -1;
  else
    return n;
}