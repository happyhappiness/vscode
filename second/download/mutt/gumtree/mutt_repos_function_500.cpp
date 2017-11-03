int mutt_check_encoding (const char *c)
{
  if (ascii_strncasecmp ("7bit", c, sizeof ("7bit")-1) == 0)
    return (ENC7BIT);
  else if (ascii_strncasecmp ("8bit", c, sizeof ("8bit")-1) == 0)
    return (ENC8BIT);
  else if (ascii_strncasecmp ("binary", c, sizeof ("binary")-1) == 0)
    return (ENCBINARY);
  else if (ascii_strncasecmp ("quoted-printable", c, sizeof ("quoted-printable")-1) == 0)
    return (ENCQUOTEDPRINTABLE);
  else if (ascii_strncasecmp ("base64", c, sizeof("base64")-1) == 0)
    return (ENCBASE64);
  else if (ascii_strncasecmp ("x-uuencode", c, sizeof("x-uuencode")-1) == 0)
    return (ENCUUENCODED);
#ifdef SUN_ATTACHMENT
  else if (ascii_strncasecmp ("uuencode", c, sizeof("uuencode")-1) == 0)
    return (ENCUUENCODED);
#endif
  else
    return (ENCOTHER);
}