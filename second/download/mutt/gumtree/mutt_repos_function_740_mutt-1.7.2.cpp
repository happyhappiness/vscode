static const unsigned char *
parse_dn_part (struct dn_array_s *array, const unsigned char *string)
{
  const unsigned char *s, *s1;
  size_t n;
  unsigned char *p;

  /* parse attributeType */
  for (s = string+1; *s && *s != '='; s++)
    ;
  if (!*s)
    return NULL; /* error */
  n = s - string;
  if (!n)
    return NULL; /* empty key */
  array->key = safe_malloc (n+1);
  p = (unsigned char *)array->key;
  memcpy (p, string, n); /* fixme: trim trailing spaces */
  p[n] = 0;
  string = s + 1;

  if (*string == '#')
    { /* hexstring */
      string++;
      for (s=string; hexdigitp (s); s++)
        s++;
      n = s - string;
      if (!n || (n & 1))
        return NULL; /* empty or odd number of digits */
      n /= 2;
      p = safe_malloc (n+1);
      array->value = (char*)p;
      for (s1=string; n; s1 += 2, n--)
        *p++ = xtoi_2 (s1);
      *p = 0;
   }
  else
    { /* regular v3 quoted string */
      for (n=0, s=string; *s; s++)
        {
          if (*s == '\\')
            { /* pair */
              s++;
              if (*s == ',' || *s == '=' || *s == '+'
                  || *s == '<' || *s == '>' || *s == '#' || *s == ';' 
                  || *s == '\\' || *s == '\"' || *s == ' ')
                n++;
              else if (hexdigitp (s) && hexdigitp (s+1))
                {
                  s++;
                  n++;
                }
              else
                return NULL; /* invalid escape sequence */
            }
          else if (*s == '\"')
            return NULL; /* invalid encoding */
          else if (*s == ',' || *s == '=' || *s == '+'
                   || *s == '<' || *s == '>' || *s == '#' || *s == ';' )
            break; 
          else
            n++;
        }

      p = safe_malloc (n+1);
      array->value = (char*)p;
      for (s=string; n; s++, n--)
        {
          if (*s == '\\')
            { 
              s++;
              if (hexdigitp (s))
                {
                  *p++ = xtoi_2 (s);
                  s++;
                }
              else
                *p++ = *s;
            }
          else
            *p++ = *s;
        }
      *p = 0;
    }
  return s;
}