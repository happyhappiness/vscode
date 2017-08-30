  char buf[1024];

  // add todays year day and month to the time in str because

  // curl_getdate no longer assumes the day is today

  sprintf(buf, "%d%02d%02d %s",

          lctime->tm_year+1900,

          lctime->tm_mon +1,

          lctime->tm_mday,

          str.c_str());

