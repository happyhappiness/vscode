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

