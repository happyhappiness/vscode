static void qp_decode_line (char *dest, char *src, size_t *l,
			    int last)
{
  char *d, *s;
  char c;

  int kind;
  int soft = 0;

  /* chop trailing whitespace */

  if (*src)
  {
    s = src + strlen(src) - 1;
    while (s >= src && ISSPACE(*s))
      s--;
    *(++s) = '\0';
  }

  /* decode the line */
  
  for (d = dest, s = src; *s;)
  {
    switch ((kind = qp_decode_triple (s, &c)))
    {
      case  0: *d++ = c; s += 3; break;	/* qp triple */
      case -1: *d++ = *s++;      break; /* single character */
      case  1: soft = 1; s++;	 break; /* soft line break */
    }
  }

  if (!soft && last == '\n')
    *d++ = '\n';
  
  *d = '\0';
  *l = d - dest;
}