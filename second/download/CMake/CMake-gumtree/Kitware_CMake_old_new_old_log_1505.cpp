sprintf(datestring, "%4d%02d%02d-%d%d",
          lctime->tm_year + 1900,
          lctime->tm_mon,
          lctime->tm_mday,
          lctime->tm_hour,
          lctime->tm_min);