void Curl_pgrsSetUploadCounter(struct Curl_easy *data, curl_off_t size)
{
  struct curltime now = Curl_tvnow();

  data->progress.uploaded = size;

  /* upload speed limit */
  if((data->set.max_send_speed > 0) &&
     (Curl_pgrsLimitWaitTime(data->progress.uploaded,
                             data->progress.ul_limit_size,
                             data->set.max_send_speed,
                             data->progress.ul_limit_start,
                             now) == 0)) {
    data->progress.ul_limit_start = now;
    data->progress.ul_limit_size = size;
  }
}