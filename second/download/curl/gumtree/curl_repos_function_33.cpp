CURLcode speedcheck(struct UrlData *data,
                    struct timeval now)
{
  static struct timeval keeps_speed;

  if((data->current_speed >= 0) &&
     data->low_speed_time &&
     (tvlong(keeps_speed) != 0) &&
     (data->current_speed < data->low_speed_limit)) {

    /* We are now below the "low speed limit". If we are below it
       for "low speed time" seconds we consider that enough reason
       to abort the download. */
    
    if( tvdiff(now, keeps_speed) > data->low_speed_time) {
      /* we have been this slow for long enough, now die */
      failf(data,
	    "Operation too slow. "
	    "Less than %d bytes/sec transfered the last %d seconds",
	    data->low_speed_limit,
	    data->low_speed_time);
      return CURLE_OPERATION_TIMEOUTED;
    }
  }
  else {
    /* we keep up the required speed all right */
    keeps_speed = now;
  }
  return CURLE_OK;
}