CURLcode Curl_speedcheck(struct SessionHandle *data,
                         struct timeval now)
{
  if((data->progress.current_speed >= 0) &&
     data->set.low_speed_time &&
     (Curl_tvlong(data->state.keeps_speed) != 0) &&
     (data->progress.current_speed < data->set.low_speed_limit)) {
    long howlong = Curl_tvdiff(now, data->state.keeps_speed);
    long nextcheck = (data->set.low_speed_time * 1000) - howlong;

    /* We are now below the "low speed limit". If we are below it
       for "low speed time" seconds we consider that enough reason
       to abort the download. */
    if(nextcheck <= 0) {
      /* we have been this slow for long enough, now die */
      failf(data,
            "Operation too slow. "
            "Less than %ld bytes/sec transferred the last %ld seconds",
            data->set.low_speed_limit,
            data->set.low_speed_time);
      return CURLE_OPERATION_TIMEDOUT;
    }
    else {
      /* wait complete low_speed_time */
      Curl_expire_latest(data, nextcheck);
    }
  }
  else {
    /* we keep up the required speed all right */
    data->state.keeps_speed = now;

    if(data->set.low_speed_limit)
      /* if there is a low speed limit enabled, we set the expire timer to
         make this connection's speed get checked again no later than when
         this time is up */
      Curl_expire_latest(data, data->set.low_speed_time*1000);
  }
  return CURLE_OK;
}