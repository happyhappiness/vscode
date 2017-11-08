void Curl_pgrsTime(struct SessionHandle *data, timerid timer)
{
  switch(timer) {
  default:
  case TIMER_NONE:
    /* mistake filter */
    break;
  case TIMER_STARTSINGLE:
    /* This is set at the start of a single fetch */
    data->progress.t_startsingle = Curl_tvnow();
    break;

  case TIMER_NAMELOOKUP:
    data->progress.t_nslookup =
      (double)Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle)/1000.0;
    break;
  case TIMER_CONNECT:
    data->progress.t_connect =
      (double)Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle)/1000.0;
    break;
  case TIMER_PRETRANSFER:
    data->progress.t_pretransfer =
      (double)Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle)/1000.0;
    break;
  case TIMER_STARTTRANSFER:
    data->progress.t_starttransfer =
      (double)Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle)/1000.0;
    break;
  case TIMER_POSTRANSFER:
    /* this is the normal end-of-transfer thing */
    break;
  case TIMER_REDIRECT:
    data->progress.t_redirect =
      (double)Curl_tvdiff(Curl_tvnow(), data->progress.start)/1000.0;
    break;
  }
}