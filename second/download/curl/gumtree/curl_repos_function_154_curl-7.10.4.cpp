void Curl_pgrsSetUploadCounter(struct SessionHandle *data, double size)
{
  data->progress.uploaded = size;
}