void Curl_pgrsTime(struct Curl_easy *data, timerid timer)
{
  struct curltime now = Curl_tvnow();
  time_t *delta = NULL;

  switch(timer) {
  default:
  case TIMER_NONE:
    /* mistake filter */
    break;
  case TIMER_STARTOP:
    /* This is set at the start of a transfer */
    data->progress.t_startop = now;
    break;
  case TIMER_STARTSINGLE:
    /* This is set at the start of each single fetch */
    data->progress.t_startsingle = now;
    data->progress.is_t_startransfer_set = false;
    break;
  case TIMER_STARTACCEPT:
    data->progress.t_acceptdata = now;
    break;
  case TIMER_NAMELOOKUP:
    delta = &data->progress.t_nslookup;
    break;
  case TIMER_CONNECT:
    delta = &data->progress.t_connect;
    break;
  case TIMER_APPCONNECT:
    delta = &data->progress.t_appconnect;
    break;
  case TIMER_PRETRANSFER:
    delta = &data->progress.t_pretransfer;
    break;
  case TIMER_STARTTRANSFER:
    delta = &data->progress.t_starttransfer;
    /* prevent updating t_starttransfer unless:
     *   1) this is the first time we're setting t_starttransfer
     *   2) a redirect has occurred since the last time t_starttransfer was set
     * This prevents repeated invocations of the function from incorrectly
     * changing the t_starttransfer time.
     */
    if(data->progress.is_t_startransfer_set) {
      return;
    }
    else {
      data->progress.is_t_startransfer_set = true;
      break;
    }
  case TIMER_POSTRANSFER:
    /* this is the normal end-of-transfer thing */
    break;
  case TIMER_REDIRECT:
    data->progress.t_redirect = Curl_tvdiff_us(now, data->progress.start);
    break;
  }
  if(delta) {
    time_t us = Curl_tvdiff_us(now, data->progress.t_startsingle);
    if(!us)
      us++; /* make sure at least one microsecond passed */
    *delta += us;
  }
}