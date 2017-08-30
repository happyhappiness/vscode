{
      struct tm *thistime;

      /* Phil Karn (Fri, 13 Apr 2001) pointed out that the If-Modified-Since
       * header family should have their times set in GMT as RFC2616 defines:
       * "All HTTP date/time stamps MUST be represented in Greenwich Mean Time
       * (GMT), without exception. For the purposes of HTTP, GMT is exactly
       * equal to UTC (Coordinated Universal Time)." (see page 20 of RFC2616).
       */

#ifdef HAVE_GMTIME_R
      /* thread-safe version */
      struct tm keeptime;
      thistime = (struct tm *)gmtime_r(&data->set.timevalue, &keeptime);
#else
      thistime = gmtime(&data->set.timevalue);
#endif

#ifdef HAVE_STRFTIME
      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
      strftime(buf, BUFSIZE-1, "%a, %d %b %Y %H:%M:%S GMT", thistime);
#else
      /* TODO: Right, we *could* write a replacement here */
      strcpy(buf, "no strftime() support");
#endif
      switch(data->set.timecondition) {
      case CURL_TIMECOND_IFMODSINCE:
      default:
        result = add_bufferf(req_buffer,
                             "If-Modified-Since: %s\r\n", buf);
        break;
      case CURL_TIMECOND_IFUNMODSINCE:
        result = add_bufferf(req_buffer,
                             "If-Unmodified-Since: %s\r\n", buf);
        break;
      case CURL_TIMECOND_LASTMOD:
        result = add_bufferf(req_buffer,
                             "Last-Modified: %s\r\n", buf);
        break;
      }
      if(result)
        return result;
    }