    }

    apr_file_close(f);
    return ret;
}

static int connect_to_daemon(int *sdptr, request_rec *r,
                             cgid_server_conf *conf)
{
    int sd;
    int connect_tries;
    apr_interval_time_t sliding_timer;

    connect_tries = 0;
    sliding_timer = 100000; /* 100 milliseconds */
    while (1) {
        ++connect_tries;
        if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
            return log_scripterror(r, conf, HTTP_INTERNAL_SERVER_ERROR, errno,
                                   "unable to create socket to cgi daemon");
        }
        if (connect(sd, (struct sockaddr *)server_addr, server_addr_len) < 0) {
            if (errno == ECONNREFUSED && connect_tries < DEFAULT_CONNECT_ATTEMPTS) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, errno, r,
                              "connect #%d to cgi daemon failed, sleeping before retry",
                              connect_tries);
                close(sd);
                apr_sleep(sliding_timer);
