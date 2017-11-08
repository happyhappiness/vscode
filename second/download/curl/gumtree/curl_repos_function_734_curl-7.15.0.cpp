static void showtime(struct SessionHandle *data,
                     const char *text,
                     time_t stamp)
{
  struct tm *tm;
#ifdef HAVE_GMTIME_R
  struct tm buffer;
  tm = (struct tm *)gmtime_r(&stamp, &buffer);
#else
  tm = gmtime(&stamp);
#endif
  snprintf(data->state.buffer,
           BUFSIZE,
           "\t %s: %s, %02d %s %4d %02d:%02d:%02d GMT\n",
           text,
           Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
           tm->tm_mday,
           Curl_month[tm->tm_mon],
           tm->tm_year + 1900,
           tm->tm_hour,
           tm->tm_min,
           tm->tm_sec);
  infof(data, "%s", data->state.buffer);
}