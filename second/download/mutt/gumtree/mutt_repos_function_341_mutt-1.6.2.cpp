static const char *km_keyname (int c)
{
  static char buf[10];
  const char *p;

  if ((p = mutt_getnamebyvalue (c, KeyNames)))
    return p;

  if (c < 256 && c > -128 && iscntrl ((unsigned char) c))
  {
    if (c < 0)
      c += 256;

    if (c < 128)
    {
      buf[0] = '^';
      buf[1] = (c + '@') & 0x7f;
      buf[2] = 0;
    }
    else
      snprintf (buf, sizeof (buf), "\\%d%d%d", c >> 6, (c >> 3) & 7, c & 7);
  }
  else if (c >= KEY_F0 && c < KEY_F(256)) /* this maximum is just a guess */
    sprintf (buf, "<F%d>", c - KEY_F0);
  else if (IsPrint (c))
    snprintf (buf, sizeof (buf), "%c", (unsigned char) c);
  else
    snprintf (buf, sizeof (buf), "\\x%hx", (unsigned short) c);
  return (buf);
}