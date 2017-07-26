  return 1;
}

static void showtime(struct Curl_easy *data,
                     const char *text,
                     time_t stamp)
{
  struct tm buffer;
  const struct tm *tm = &buffer;
  CURLcode result = Curl_gmtime(stamp, &buffer);
  if(result)
    return;

  snprintf(data->state.buffer,
           BUFSIZE,
           "\t %s: %s, %02d %s %4d %02d:%02d:%02d GMT",
           text,
           Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
