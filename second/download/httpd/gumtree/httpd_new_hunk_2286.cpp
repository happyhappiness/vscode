            if (space)

                return;

            else {

                /* header is in invalid or too big - close connection */

                close(c->fd);

                if (bad++ > 10) {

                    err("\nTest aborted after 10 failures\n\n");

                }

                FD_CLR(c->fd, &writebits);

                start_connect(c);

            }

        }

        else {

