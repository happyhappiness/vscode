ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "proxy: Closing connection to client because"
                              " reading from backend server %s failed. Number"
                              " of keepalives %i", backend->hostname, 
                              c->keepalives);