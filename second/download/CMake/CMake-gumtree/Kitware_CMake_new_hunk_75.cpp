      /* we got a time. Format should be: "YYYYMMDDHHMMSS[.sss]" where the

         last .sss part is optional and means fractions of a second */

      int year, month, day, hour, minute, second;

      if(6 == sscanf(&data->state.buffer[4], "%04d%02d%02d%02d%02d%02d",

                     &year, &month, &day, &hour, &minute, &second)) {

        /* we have a time, reformat it */

        char timebuf[24];

        time_t secs=time(NULL);



        snprintf(timebuf, sizeof(timebuf),

                 "%04d%02d%02d %02d:%02d:%02d GMT",

                 year, month, day, hour, minute, second);

        /* now, convert this into a time() value: */

        data->info.filetime = (long)curl_getdate(timebuf, &secs);

      }



#ifdef CURL_FTP_HTTPSTYLE_HEAD

