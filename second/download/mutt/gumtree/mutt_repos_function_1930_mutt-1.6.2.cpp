int imap_get_literal_count(const char *buf, long *bytes)
{
  char *pc;
  char *pn;

  if (!buf || !(pc = strchr (buf, '{')))
    return -1;

  pc++;
  pn = pc;
  while (isdigit ((unsigned char) *pc))
    pc++;
  *pc = 0;
  *bytes = atoi(pn);

  return 0;
}