  return 1;

}



#ifndef CURL_DISABLE_VERBOSE_STRINGS

static void showtime(struct Curl_easy *data,

                     const char *text,

                     time_t stamp)

{

  struct tm buffer;

  const struct tm *tm = &buffer;

  char str[96];

  CURLcode result = Curl_gmtime(stamp, &buffer);

  if(result)

    return;



  snprintf(str,

           sizeof(str),

           "\t %s: %s, %02d %s %4d %02d:%02d:%02d GMT",

           text,

           Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],

