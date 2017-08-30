          return result;



        /* format: "Tue, 15 Nov 1994 12:45:26" */

        snprintf(headerbuf, sizeof(headerbuf),

                 "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",

                 Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],

                 tm->tm_mday,

