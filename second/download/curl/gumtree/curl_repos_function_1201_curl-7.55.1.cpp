void Curl_pgrsResetTimesSizes(struct Curl_easy *data)
{
  data->progress.t_nslookup = 0;
  data->progress.t_connect = 0;
  data->progress.t_pretransfer = 0;
  data->progress.t_starttransfer = 0;

  Curl_pgrsSetDownloadSize(data, -1);
  Curl_pgrsSetUploadSize(data, -1);
}