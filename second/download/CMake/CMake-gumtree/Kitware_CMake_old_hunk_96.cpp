        /* we have a time, reformat it */

        time_t secs=time(NULL);

        /* using the good old yacc/bison yuck */

        snprintf(buf, sizeof(conn->data->state.buffer),

                 "%04d%02d%02d %02d:%02d:%02d GMT",

                 year, month, day, hour, minute, second);

        /* now, convert this into a time() value: */

