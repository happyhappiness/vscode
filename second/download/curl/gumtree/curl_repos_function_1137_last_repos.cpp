CURLcode Curl_speedcheck(struct Curl_easy *data,
                         struct curltime now)
{
  if((data->progress.current_speed >= 0) && data->set.low_speed_time) {
    if(data->progress.current_speed < data->set.low_speed_limit) {
      if(!data->state.keeps_speed.tv_sec)
        /* under the limit at this very moment */
        data->state.keeps_speed = now;
      else {
        /* how long has it been under the limit */
        time_t howlong = Curl_tvdiff(now, data->state.keeps_speed);

        if(howlong >= data->set.low_speed_time * 1000) {
          /* too long */
          failf(data,
                "Operation too slow. "
                "Less than %ld bytes/sec transferred the last %ld seconds",
                data->set.low_speed_limit,
                data->set.low_speed_time);
          return CURLE_OPERATION_TIMEDOUT;
        }
      }
    }
    else
      /* faster right now */
      data->state.keeps_speed.tv_sec = 0;
  }

  if(data->set.low_speed_limit)
    /* if low speed limit is enabled, set the expire timer to make this
       connection's speed get checked again in a second */
    Curl_expire(data, 1000, EXPIRE_SPEEDCHECK);

  return CURLE_OK;
}