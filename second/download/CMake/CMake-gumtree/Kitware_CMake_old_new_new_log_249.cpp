snprintf(buf, BUFSIZE-1,
             "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
             Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
             tm->tm_mday,
             Curl_month[tm->tm_mon],
             tm->tm_year + 1900,
             tm->tm_hour,
             tm->tm_min,
             tm->tm_sec);