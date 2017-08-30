                     &year, &month, &day, &hour, &minute, &second)) {

        /* we have a time, reformat it */

        time_t secs=time(NULL);

        snprintf(buf, sizeof(conn->data->state.buffer),

                 "%04d%02d%02d %02d:%02d:%02d GMT",

                 year, month, day, hour, minute, second);

        /* now, convert this into a time() value: */

        conn->data->info.filetime = curl_getdate(buf, &secs);

      }

