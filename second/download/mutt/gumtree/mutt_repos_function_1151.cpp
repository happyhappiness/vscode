static int mbox_to_udomain (const char *mbx, char **user, char **domain)
{
  static char *buff = NULL;
  char *p;

  mutt_str_replace (&buff, mbx);

  p = strchr (buff, '@');
  if (!p || !p[1])
    return -1;
  *p = '\0';
  *user = buff;
  *domain  = p + 1;
  return 0;
}