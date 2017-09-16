            return;

        }

        else {

            close(c->fd);

            err_conn++;

            if (bad++ > 10) {

                printf("\nTest aborted after 10 failures\n\n");

                exit(1);

            }

            start_connect(c);

        }

    }



    /* connected first time */

