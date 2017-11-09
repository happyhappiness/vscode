static void fake_t_startsingle_time(struct Curl_easy *data,
                                    struct curltime fake_now,
                                    int seconds_offset)
{
  Curl_pgrsTime(data, TIMER_STARTSINGLE);
  data->progress.t_startsingle.tv_sec = fake_now.tv_sec + seconds_offset;
  data->progress.t_startsingle.tv_usec = fake_now.tv_usec;
}