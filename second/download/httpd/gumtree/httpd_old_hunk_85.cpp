            output_results();
        }

        /* Timeout of 30 seconds. */
        timeout.tv_sec = 30;
        timeout.tv_usec = 0;
        n = select(256, &sel_read, &sel_write, &sel_except, &timeout);
        if (!n) {
            printf("\nServer timed out\n\n");
            exit(1);
        }
        if (n < 1)
            err("select");
