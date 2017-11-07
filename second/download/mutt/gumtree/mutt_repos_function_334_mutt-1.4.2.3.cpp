int mx_set_magic (const char *s)
{
  if (ascii_strcasecmp (s, "mbox") == 0)
    DefaultMagic = M_MBOX;
  else if (ascii_strcasecmp (s, "mmdf") == 0)
    DefaultMagic = M_MMDF;
  else if (ascii_strcasecmp (s, "mh") == 0)
    DefaultMagic = M_MH;
  else if (ascii_strcasecmp (s, "maildir") == 0)
    DefaultMagic = M_MAILDIR;
  else if (ascii_strcasecmp (s, "kendra") == 0)
    DefaultMagic = M_KENDRA;
  else
    return (-1);

  return 0;
}