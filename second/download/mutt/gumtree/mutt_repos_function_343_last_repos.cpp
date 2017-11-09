static int parsekeys (const char *str, keycode_t *d, int max)
{
  int n, len = max;
  char buff[SHORT_STRING];
  char c;
  char *s, *t;

  strfcpy(buff, str, sizeof(buff));
  s = buff;
  
  while (*s && len)
  {
    *d = '\0';
    if(*s == '<' && (t = strchr(s, '>')))
    {
      t++; c = *t; *t = '\0';
      
      if ((n = mutt_getvaluebyname (s, KeyNames)) != -1)
      {
	s = t;
	*d = n;
      }
      else if ((n = parse_fkey(s)) > 0)
      {
	s = t;
	*d = KEY_F (n);
      }
      else if ((n = parse_keycode(s)) > 0)
      {
	s = t;
	*d = n;
      }
      
      *t = c;
    }

    if(!*d)
    {
      *d = (unsigned char)*s;
      s++;
    }
    d++;
    len--;
  }

  return (max - len);
}