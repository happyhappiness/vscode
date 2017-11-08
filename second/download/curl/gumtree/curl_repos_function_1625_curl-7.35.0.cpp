static long ftp_timeleft_accept(struct SessionHandle *data)
{
  long timeout_ms = DEFAULT_ACCEPT_TIMEOUT;
  long other;
  struct timeval now;

  if(data->set.accepttimeout > 0)
    timeout_ms = data->set.accepttimeout;

  now = Curl_tvnow();

  /* check if the generic timeout possibly is set shorter */
  other =  Curl_timeleft(data, &now, FALSE);
  if(other && (other < timeout_ms))
    /* note that this also works fine for when other happens to be negative
       due to it already having elapsed */
    timeout_ms = other;
  else {
    /* subtract elapsed time */
    timeout_ms -= Curl_tvdiff(now, data->progress.t_acceptdata);
    if(!timeout_ms)
      /* avoid returning 0 as that means no timeout! */
      return -1;
  }

  return timeout_ms;
}