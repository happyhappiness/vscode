
            /* if we are done, leave */
            if (TRUE == finish) {
                break;
            }
        }
        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, "end body send");

    }
    if (data_sock) {
        ap_flush_conn(data);
        apr_socket_close(data_sock);
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01058) "data connection closed");
    }

    /* Retrieve the final response for the RETR or LIST commands */
    proxy_ftp_command(NULL, r, origin, bb, &ftpmessage);
    apr_brigade_cleanup(bb);

    /*
     * VII: Clean Up -------------
     *
     * If there are no KeepAlives, or if the connection has been signalled to
     * close, close the socket and clean up
     */

    /* finish */
    proxy_ftp_command("QUIT" CRLF, r, origin, bb, &ftpmessage);
    /* responses: 221, 500 */
    /* 221 Service closing control connection. */
    /* 500 Syntax error, command unrecognized. */
    ap_flush_conn(origin);
    proxy_ftp_cleanup(r, backend);

