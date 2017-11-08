time_t Curl_timeleft(struct Curl_easy *data,
                     struct curltime *nowp,
                     bool duringconnect)
{
  int timeout_set = 0;
  time_t timeout_ms = duringconnect?DEFAULT_CONNECT_TIMEOUT:0;
  struct curltime now;

  /* if a timeout is set, use the most restrictive one */

  if(data->set.timeout > 0)
    timeout_set |= 1;
  if(duringconnect && (data->set.connecttimeout > 0))
    timeout_set |= 2;

  switch(timeout_set) {
  case 1:
    timeout_ms = data->set.timeout;
    break;
  case 2:
    timeout_ms = data->set.connecttimeout;
    break;
  case 3:
    if(data->set.timeout < data->set.connecttimeout)
      timeout_ms = data->set.timeout;
    else
      timeout_ms = data->set.connecttimeout;
    break;
  default:
    /* use the default */
    if(!duringconnect)
      /* if we're not during connect, there's no default timeout so if we're
         at zero we better just return zero and not make it a negative number
         by the math below */
      return 0;
    break;
  }

  if(!nowp) {
    now = Curl_tvnow();
    nowp = &now;
  }

  /* subtract elapsed time */
  if(duringconnect)
    /* since this most recent connect started */
    timeout_ms -= Curl_tvdiff(*nowp, data->progress.t_startsingle);
  else
    /* since the entire operation started */
    timeout_ms -= Curl_tvdiff(*nowp, data->progress.t_startop);
  if(!timeout_ms)
    /* avoid returning 0 as that means no timeout! */
    return -1;

  return timeout_ms;
}