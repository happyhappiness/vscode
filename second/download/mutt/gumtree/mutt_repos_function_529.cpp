int mx_set_magic (const char *s)
{
  if (ascii_strcasecmp (s, "mbox") == 0)
    DefaultMagic = MUTT_MBOX;
  else if (ascii_strcasecmp (s, "mmdf") == 0)
    DefaultMagic = MUTT_MMDF;
  else if (ascii_strcasecmp (s, "mh") == 0)
    DefaultMagic = MUTT_MH;
  else if (ascii_strcasecmp (s, "maildir") == 0)
    DefaultMagic = MUTT_MAILDIR;
  else
    return (-1);

  return 0;
}