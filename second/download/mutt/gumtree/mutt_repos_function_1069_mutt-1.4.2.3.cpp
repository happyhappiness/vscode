static int check_uidl (char *line, void *data)
{
  int i;
  unsigned int index;
  CONTEXT *ctx = (CONTEXT *)data;

  sscanf (line, "%u %s", &index, line);
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