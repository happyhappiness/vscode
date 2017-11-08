long Curl_pgrsLimitWaitTime(curl_off_t cursize,
                            curl_off_t startsize,
                            curl_off_t limit,
                            struct timeval start,
                            struct timeval now)
{
    curl_off_t size = cursize - startsize;
    long minimum, actual;

    /* we don't have a starting point yet -- return 0 so it gets (re)set */
    if(start.tv_sec == 0 && start.tv_usec == 0)
        return 0;

    /* not enough data yet */
    if(size < limit)
      return -1;

    minimum = (long) (CURL_OFF_T_C(1000) * size / limit);
    actual = Curl_tvdiff(now, start);

    if(actual < minimum)
      return minimum - actual;
    else
      return 0;
}