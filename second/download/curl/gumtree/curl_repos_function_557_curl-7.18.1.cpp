void Curl_pgrsSetDownloadCounter(struct SessionHandle *data, curl_off_t size)
{
  data->progress.downloaded = size;
}