#ifdef HAVE_GMTIME_R
      /* thread-safe version */
      struct tm keeptime;
      tm = (struct tm *)gmtime_r(&data->set.timevalue, &keeptime);
#else
      tm = gmtime(&data->set.timevalue);
#endif

      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
      snprintf(buf, BUFSIZE-1,
               "%s, %02d %s %4d %02d:%02d:%02d GMT",
               Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
               tm->tm_mday,
               Curl_month[tm->tm_mon],
               tm->tm_year + 1900,
               tm->tm_hour,
               tm->tm_min,
               tm->tm_sec);

      switch(data->set.timecondition) {
      case CURL_TIMECOND_IFMODSINCE:
      default:
