            err_conn++;
            if (bad++ > 10) {
                fprintf(stderr,
                   "\nTest aborted after 10 failures\n\n");
                apr_err("apr_socket_connect()", rv);
            }

            start_connect(c);
            return;
        }
    }

    /* connected first time */
