void Curl_pgrsSetDownloadCounter(struct Curl_easy *data, curl_off_t size)
{
  struct curltime now = Curl_tvnow();

  data->progress.downloaded = size;

  /* download speed limit */
  if((data->set.max_recv_speed > 0) &&
     (Curl_pgrsLimitWaitTime(data->progress.downloaded,
                             data->progress.dl_limit_size,
                             data->set.max_recv_speed,
                             data->progress.dl_limit_start,
                             now) == 0)) {
    data->progress.dl_limit_start = now;
    data->progress.dl_limit_size = size;
  }
}