void pgrsTime(struct UrlData *data, timerid timer)
{
  switch(timer) {
  default:
  case TIMER_NONE:
    /* mistake filter */
    break;
  case TIMER_NAMELOOKUP:
    data->progress.t_nslookup = tvnow();
    break;
  case TIMER_CONNECT:
    data->progress.t_connect = tvnow();
    break;
  case TIMER_PRETRANSFER:
    data->progress.t_pretransfer = tvnow();
    break;
  case TIMER_POSTRANSFER:
    /* this is the normal end-of-transfer thing */
    break;
  }
}