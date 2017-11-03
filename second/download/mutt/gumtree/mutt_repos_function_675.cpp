static int
digit_or_letter (const unsigned char *s)
{
  return ( (*s >= '0' && *s < '9')
           || (*s >= 'A' && *s <= 'Z')
           || (*s >= 'a' && *s <= 'z'));
}