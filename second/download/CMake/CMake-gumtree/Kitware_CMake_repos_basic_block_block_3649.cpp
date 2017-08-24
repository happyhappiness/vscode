f(Curl_pgrsUpdate(conn))
      result = CURLE_ABORTED_BY_CALLBACK;
    else {
      struct timeval now2 = Curl_tvnow();
      time_t timediff = Curl_tvdiff(now2, now); /* spent time */
      if(timediff <= 0)
        timeout -= 1; /* always deduct at least 1 */
      else if(timediff > timeout)
        timeout = -1;
      else
        timeout -= (long)timediff;
      now = now2; /* for next loop */
    }