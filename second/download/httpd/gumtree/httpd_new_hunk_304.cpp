            return;
        }
        else {
            close(c->fd);
            err_conn++;
            if (bad++ > 10) {
                err("\nTest aborted after 10 failures\n\n");
            }
            start_connect(c);
        }
    }

    /* connected first time */
