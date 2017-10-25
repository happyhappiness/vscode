void pgrsSetDownloadCounter(struct UrlData *data, double size)
{
  data->progress.downloaded = size;
}