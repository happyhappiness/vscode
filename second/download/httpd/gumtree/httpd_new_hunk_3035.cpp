                 */
                ap_flush_conn(data);
                if (data_sock) {
                    apr_socket_close(data_sock);
                }
                data_sock = NULL;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01057)
                              "data connection closed");
                /* signal that we must leave */
                finish = TRUE;
            }

            /* if no EOS yet, then we must flush */
            if (FALSE == finish) {
