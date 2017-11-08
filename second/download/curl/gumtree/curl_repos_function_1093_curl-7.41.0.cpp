void Curl_pgrsTime(struct SessionHandle *data, timerid timer)
{
  struct timeval now = Curl_tvnow();

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
    break;

  case TIMER_STARTACCEPT:
    data->progress.t_acceptdata = Curl_tvnow();
    break;

  case TIMER_NAMELOOKUP:
    data->progress.t_nslookup =
      Curl_tvdiff_secs(now, data->progress.t_startsingle);
    break;
  case TIMER_CONNECT:
    data->progress.t_connect =
      Curl_tvdiff_secs(now, data->progress.t_startsingle);
    break;
  case TIMER_APPCONNECT:
    data->progress.t_appconnect =
      Curl_tvdiff_secs(now, data->progress.t_startsingle);
    break;
  case TIMER_PRETRANSFER:
    data->progress.t_pretransfer =
      Curl_tvdiff_secs(now, data->progress.t_startsingle);
    break;
  case TIMER_STARTTRANSFER:
    data->progress.t_starttransfer =
      Curl_tvdiff_secs(now, data->progress.t_startsingle);
    break;
  case TIMER_POSTRANSFER:
    /* this is the normal end-of-transfer thing */
    break;
  case TIMER_REDIRECT:
    data->progress.t_redirect = Curl_tvdiff_secs(now, data->progress.start);
    break;
  }
}