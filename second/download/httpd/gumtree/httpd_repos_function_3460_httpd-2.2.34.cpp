int main(int argc, char *argv[])
{
    apr_pool_t *p;
    apr_status_t rv;

#ifdef SIGPIPE
    signal(SIGPIPE, SIG_IGN);
#endif

    rv = apr_initialize();
    if (rv != APR_SUCCESS) {
        aprerr("apr_initialize()", rv);
    }

    atexit(apr_terminate);

    rv = apr_pool_create(&p, NULL);
    if (rv != APR_SUCCESS) {
        aprerr("apr_pool_create()", rv);
    }

    if (argc >= 2 && !strcmp(argv[1], "client")) {
        const char *host = NULL;
        int mode = BLK;
        int start_server = 0;
        int i;

        for (i = 2; i < argc; i++) {
            if (!strcmp(argv[i], "blocking")) {
                mode = BLK;
            }
            else if (!strcmp(argv[i], "timeout")) {
                mode = TIMEOUT;
            }
            else if (!strcmp(argv[i], "nonblocking")) {
                mode = NONBLK;
            }
            else if (!strcmp(argv[i], "startserver")) {
                start_server = 1;
            }
            else {
                host = argv[i];
            }	
        }
        return client(p, mode, host, start_server);
    }
    else if (argc == 2 && !strcmp(argv[1], "server")) {
        return server(p);
    }

    fprintf(stderr, 
            "Usage: %s client {blocking|nonblocking|timeout} [startserver] [server-host]\n"
            "       %s server\n",
            argv[0], argv[0]);
    return -1;
}