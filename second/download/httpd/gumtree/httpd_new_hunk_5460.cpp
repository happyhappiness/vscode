            else if (w < 0) {
                if (r->connection->aborted)
                    break;
                else if (errno == EAGAIN)
                    continue;
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_INFO, r,
                     "client stopped connection before send mmap completed");
                    ap_bsetflag(r->connection->client, B_EOUT, 1);
                    r->connection->aborted = 1;
                    break;
                }
            }
        }
