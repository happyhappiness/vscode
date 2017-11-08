void Curl_pgrsTime(struct SessionHandle *data, timerid timer)
{
  switch(timer) {
  default:
  case TIMER_NONE:
    /* mistake filter */
    break;
  case TIMER_STARTSINGLE:
    /* This is set at the start of a single fetch, there may be several
       fetches within an operation, why we add all other times relative
       to this one */
    data->progress.t_startsingle = Curl_tvnow();
    break;

  case TIMER_NAMELOOKUP:
    data->progress.t_nslookup += Curl_tvdiff(Curl_tvnow(),
                                        data->progress.t_startsingle);
    break;
  case TIMER_CONNECT:
    data->progress.t_connect += Curl_tvdiff(Curl_tvnow(),
                                       data->progress.t_startsingle);
    break;
  case TIMER_PRETRANSFER:
    data->progress.t_pretransfer += Curl_tvdiff(Curl_tvnow(),
                                           data->progress.t_startsingle);
    break;
  case TIMER_POSTRANSFER:
    /* this is the normal end-of-transfer thing */
    break;
  }
}