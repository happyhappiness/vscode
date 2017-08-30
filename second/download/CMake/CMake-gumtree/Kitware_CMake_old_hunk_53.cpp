   */



  /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */

  snprintf(buf, BUFSIZE-1,

           "%s, %02d %s %4d %02d:%02d:%02d GMT",

           Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],

           tm->tm_mday,

           Curl_month[tm->tm_mon],

