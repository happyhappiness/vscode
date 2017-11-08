void Curl_pgrsSetUploadCounter(struct SessionHandle *data, curl_off_t size)
{
  data->progress.uploaded = size;
}