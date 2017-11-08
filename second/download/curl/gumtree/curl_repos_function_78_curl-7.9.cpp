void Curl_pgrsSetDownloadCounter(struct SessionHandle *data, double size)
{
  data->progress.downloaded = size;
}