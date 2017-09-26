                /* if this is the last brigade, cleanup the
                 * backend connection first to prevent the
                 * backend server from hanging around waiting
                 * for a slow client to eat these bytes
                 */
                ap_flush_conn(data);
                apr_socket_close(data_sock);
                data_sock = NULL;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: FTP: data connection closed");
                /* signal that we must leave */
                finish = TRUE;
            }
