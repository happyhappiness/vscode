CURLcode Curl_speedcheck(struct SessionHandle *data,
                         struct timeval now)
{
  if((data->progress.current_speed >= 0) &&
     data->set.low_speed_time &&
     (Curl_tvlong(data->state.keeps_speed) != 0) &&
     (data->progress.current_speed < data->set.low_speed_limit)) {

    /* We are now below the "low speed limit". If we are below it
       for "low speed time" seconds we consider that enough reason
       to abort the download. */

    if( (Curl_tvdiff(now, data->state.keeps_speed)/1000) >
        data->set.low_speed_time) {
      /* we have been this slow for long enough, now die */
      failf(data,
            "Operation too slow. "
            "Less than %d bytes/sec transfered the last %d seconds",
            data->set.low_speed_limit,
            data->set.low_speed_time);
      return CURLE_OPERATION_TIMEOUTED;
    }
  }
  else {
    /* we keep up the required speed all right */
    data->state.keeps_speed = now;
  }
  return CURLE_OK;
}