void Curl_pgrsResetTimes(struct SessionHandle *data)
{
  data->progress.t_nslookup = 0.0;
  data->progress.t_connect = 0.0;
  data->progress.t_pretransfer = 0.0;
  data->progress.t_starttransfer = 0.0;
}