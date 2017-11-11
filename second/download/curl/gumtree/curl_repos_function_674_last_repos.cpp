static int runawhile(long time_limit,
                     long speed_limit,
                     curl_off_t speed,
                     int dec)
{
  int counter = 1;
  struct curltime now = {1, 0};
  CURLcode result;
  int finaltime;

  curl_easy_setopt(easy, CURLOPT_LOW_SPEED_LIMIT, speed_limit);
  curl_easy_setopt(easy, CURLOPT_LOW_SPEED_TIME, time_limit);
  Curl_speedinit(easy);

  do {
    /* fake the current transfer speed */
    easy->progress.current_speed = speed;
    result = Curl_speedcheck(easy, now);
    if(result)
      break;
    /* step the time */
    now.tv_sec = ++counter;
    speed -= dec;
  } while(counter < 100);

  finaltime = (int)(now.tv_sec - 1);

  return finaltime;
}