ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                   "proxy: NOT Closing connection to client"
                                   " although reading from backend server %s:%d"
                                   " failed.", backend->hostname,
                                   backend->port);