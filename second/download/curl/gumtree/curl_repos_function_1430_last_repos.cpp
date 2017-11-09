CURLcode Curl_add_timecondition(struct Curl_easy *data,
                                Curl_send_buffer *req_buffer)
{
  const struct tm *tm;
  struct tm keeptime;
  CURLcode result;
  char datestr[80];
  const char *condp;

  if(data->set.timecondition == CURL_TIMECOND_NONE)
    /* no condition was asked for */
    return CURLE_OK;

  result = Curl_gmtime(data->set.timevalue, &keeptime);
  if(result) {
    failf(data, "Invalid TIMEVALUE");
    return result;
  }
  tm = &keeptime;

  switch(data->set.timecondition) {
  default:
    return CURLE_BAD_FUNCTION_ARGUMENT;

  case CURL_TIMECOND_IFMODSINCE:
    condp = "If-Modified-Since";
    break;
  case CURL_TIMECOND_IFUNMODSINCE:
    condp = "If-Unmodified-Since";
    break;
  case CURL_TIMECOND_LASTMOD:
    condp = "Last-Modified";
    break;
  }

  /* The If-Modified-Since header family should have their times set in
   * GMT as RFC2616 defines: "All HTTP date/time stamps MUST be
   * represented in Greenwich Mean Time (GMT), without exception. For the
   * purposes of HTTP, GMT is exactly equal to UTC (Coordinated Universal
   * Time)." (see page 20 of RFC2616).
   */

  /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
  snprintf(datestr, sizeof(datestr),
           "%s: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
           condp,
           Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
           tm->tm_mday,
           Curl_month[tm->tm_mon],
           tm->tm_year + 1900,
           tm->tm_hour,
           tm->tm_min,
           tm->tm_sec);

  result = Curl_add_buffer(req_buffer, datestr, strlen(datestr));

  return result;
}