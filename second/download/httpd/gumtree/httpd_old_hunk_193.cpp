{
    if (sig == SIGHUP) {
        ++daemon_should_exit;
    }
}

static int cgid_server(void *data) 
{ 
    struct sockaddr_un unix_addr;
    int sd, sd2, rc;
    mode_t omask;
    apr_socklen_t len;
