            if (space)

                return;

            else {

                /* header is in invalid or too big - close connection */

                close(c->fd);

                if (bad++ > 10) {

                    printf("\nTest aborted after 10 failures\n\n");

                    exit(1);

                }

                FD_CLR(c->fd, &writebits);

                start_connect(c);

            }

        }

        else {

