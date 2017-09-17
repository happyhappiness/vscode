            output_results();
        }

        /* Timeout of 30 seconds. */
        timeout.tv_sec = 30;
        timeout.tv_usec = 0;
        n = ap_select(FD_SETSIZE, &sel_read, &sel_write, &sel_except, &timeout);
        if (!n) {
            printf("\nServer timed out\n\n");
            exit(1);
        }
        if (n < 1)
            err("select");
++ apache_1.3.1/src/support/htdigest.c	1998-07-13 19:32:58.000000000 +0800
