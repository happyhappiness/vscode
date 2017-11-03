static int check_uidl (char *line, void *data)
{
  int i;
  unsigned int index;
  CONTEXT *ctx = (CONTEXT *)data;
  char *endp;

  errno = 0;
  index = strtoul(line, &endp, 10);
  if (errno)
      return -1;
  while (*endp == ' ')
      endp++;
  memmove(line, endp, strlen(endp) + 1);

  for (i = 0; i < ctx->msgcount; i++)
  {
    if (!mutt_strcmp (ctx->hdrs[i]->data, line))
    {
      ctx->hdrs[i]->refno = index;
      break;
    }
  }

  return 0;
}