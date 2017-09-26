                backend_failed = 1;
                break;
        }

        /*
         * If connection has been aborted by client: Stop working.
         * Nevertheless, we regard our operation so far as a success:
         * So reset output_failed to 0 and set result to CMD_AJP13_END_RESPONSE
         * But: Close this connection to the backend.
         */
        if (r->connection->aborted) {
            conn->close++;
            output_failed = 0;
            result = CMD_AJP13_END_RESPONSE;
            request_ended = 1;
        }

        /*
         * We either have finished successfully or we failed.
         * So bail out
         */
        if ((result == CMD_AJP13_END_RESPONSE) || backend_failed
            || output_failed)
            break;

        /* read the response */
        status = ajp_read_header(conn->sock, r, maxsize,
                                 (ajp_msg_t **)&(conn->data));
        if (status != APR_SUCCESS) {
