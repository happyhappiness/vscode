void ProgressEnd(struct UrlData *data)
{
  if(data->conf&(CONF_NOPROGRESS|CONF_MUTE))
    return;
  fputs("\n", stderr);
}