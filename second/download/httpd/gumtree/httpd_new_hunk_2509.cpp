        memcpy(&sel_write, &writebits, sizeof(readbits));



        /* check for time limit expiry */

        gettimeofday(&now, 0);

        if (tlimit && timedif(now, start) > (tlimit * 1000)) {

            requests = done;    /* so stats are correct */

        }



        /* Timeout of 30 seconds. */

        timeout.tv_sec = 30;

        timeout.tv_usec = 0;

        n = ap_select(FD_SETSIZE, &sel_read, &sel_write, &sel_except, &timeout);

        if (!n) {

            err("\nServer timed out\n\n");

        }

        if (n < 1)

            err("select");



        for (i = 0; i < concurrency; i++) {

            int s = con[i].fd;

