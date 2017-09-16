            else if (w < 0) {

                if (r->connection->aborted)

                    break;

                else if (errno == EAGAIN)

                    continue;

                else {

                    ap_log_error(APLOG_MARK, APLOG_INFO, r->server,

                     "%s client stopped connection before send mmap completed",

                                ap_get_remote_host(r->connection,

                                                r->per_dir_config,

                                                REMOTE_NAME));

                    ap_bsetflag(r->connection->client, B_EOUT, 1);

                    r->connection->aborted = 1;

                    break;

                }

            }

        }

