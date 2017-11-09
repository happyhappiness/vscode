long Curl_pgrsLimitWaitTime(curl_off_t cursize,
                            curl_off_t startsize,
                            curl_off_t limit,
                            struct curltime start,
                            struct curltime now)
{
  curl_off_t size = cursize - startsize;
  time_t minimum;
  time_t actual;

  /* we don't have a starting point yet -- return 0 so it gets (re)set */
  if(start.tv_sec == 0 && start.tv_usec == 0)
    return 0;

  /* not enough data yet */
  if(size < limit)
    return -1;

  minimum = (time_t) (CURL_OFF_T_C(1000) * size / limit);
  actual = Curl_tvdiff(now, start);

  if(actual < minimum)
    /* this is a conversion on some systems (64bit time_t => 32bit long) */
    return (long)(minimum - actual);

  return 0;
}