static int WriteProc(void *param, char *text, int len)
{
  struct UrlData *data = (struct UrlData *)param;

  data->fwrite(text, 1, strlen(text), data->out);
  return 0;
}