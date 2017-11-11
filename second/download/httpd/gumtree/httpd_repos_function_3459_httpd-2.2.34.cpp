static int server(apr_pool_t *p)
{
    apr_status_t rv;
    apr_socket_t *sock;
    char buf[120];
    int i;
    apr_socket_t *newsock = NULL;
    apr_size_t bytes_read;
    apr_sockaddr_t *localsa;
    int family;

    family = APR_INET;
    apr_setup(p, &sock, &family);

    rv = apr_socket_opt_set(sock, APR_SO_REUSEADDR, 1);
    if (rv != APR_SUCCESS) {
        aprerr("apr_socket_opt_set()", rv);
    }

    rv = apr_sockaddr_info_get(&localsa, NULL, family, TESTSF_PORT, 0, p);
    if (rv != APR_SUCCESS) {
        aprerr("apr_sockaddr_info_get()", rv);
    }

    rv = apr_socket_bind(sock, localsa);
    if (rv != APR_SUCCESS) {
        aprerr("apr_socket_bind()", rv);
    }

    rv = apr_socket_listen(sock, 5);
    if (rv != APR_SUCCESS) {
        aprerr("apr_socket_listen()", rv);
    }

    printf("Waiting for a client to connect...\n");

    rv = apr_socket_accept(&newsock, sock, p);
    if (rv != APR_SUCCESS) {
        aprerr("apr_socket_accept()", rv);
    }

    printf("Processing a client...\n");

    assert(sizeof buf > strlen(HDR1));
    bytes_read = strlen(HDR1);
    rv = apr_socket_recv(newsock, buf, &bytes_read);
    if (rv != APR_SUCCESS) {
        aprerr("apr_socket_recv()", rv);
    }
    if (bytes_read != strlen(HDR1)) {
        fprintf(stderr, "wrong data read (1)\n");
        exit(1);
    }
    if (memcmp(buf, HDR1, strlen(HDR1))) {
        fprintf(stderr, "wrong data read (2)\n");
        fprintf(stderr, "received: `%.*s'\nexpected: `%s'\n",
                (int)bytes_read, buf, HDR1);
        exit(1);
    }
        
    assert(sizeof buf > strlen(HDR2));
    bytes_read = strlen(HDR2);
    rv = apr_socket_recv(newsock, buf, &bytes_read);
    if (rv != APR_SUCCESS) {
        aprerr("apr_socket_recv()", rv);
    }
    if (bytes_read != strlen(HDR2)) {
        fprintf(stderr, "wrong data read (3)\n");
        exit(1);
    }
    if (memcmp(buf, HDR2, strlen(HDR2))) {
        fprintf(stderr, "wrong data read (4)\n");
        fprintf(stderr, "received: `%.*s'\nexpected: `%s'\n",
                (int)bytes_read, buf, HDR2);
        exit(1);
    }

    for (i = 0; i < HDR3_LEN; i++) {
        bytes_read = 1;
        rv = apr_socket_recv(newsock, buf, &bytes_read);
        if (rv != APR_SUCCESS) {
            aprerr("apr_socket_recv()", rv);
        }
        if (bytes_read != 1) {
            fprintf(stderr, "apr_socket_recv()->%ld bytes instead of 1\n",
                    (long int)bytes_read);
            exit(1);
        }
        if (buf[0] != HDR3_CHAR) {
            fprintf(stderr,
                    "problem with data read (byte %d of hdr 3):\n",
                    i);
            fprintf(stderr, "read `%c' (0x%x) from client; expected "
                    "`%c'\n",
                    buf[0], buf[0], HDR3_CHAR);
            exit(1);
        }
    }
        
    for (i = 0; i < FILE_LENGTH; i++) {
        bytes_read = 1;
        rv = apr_socket_recv(newsock, buf, &bytes_read);
        if (rv != APR_SUCCESS) {
            aprerr("apr_socket_recv()", rv);
        }
        if (bytes_read != 1) {
            fprintf(stderr, "apr_socket_recv()->%ld bytes instead of 1\n",
                    (long int)bytes_read);
            exit(1);
        }
        if (buf[0] != FILE_DATA_CHAR) {
            fprintf(stderr,
                    "problem with data read (byte %d of file):\n",
                    i);
            fprintf(stderr, "read `%c' (0x%x) from client; expected "
                    "`%c'\n",
                    buf[0], buf[0], FILE_DATA_CHAR);
            exit(1);
        }
    }
        
    assert(sizeof buf > strlen(TRL1));
    bytes_read = strlen(TRL1);
    rv = apr_socket_recv(newsock, buf, &bytes_read);
    if (rv != APR_SUCCESS) {
        aprerr("apr_socket_recv()", rv);
    }
    if (bytes_read != strlen(TRL1)) {
        fprintf(stderr, "wrong data read (5)\n");
        exit(1);
    }
    if (memcmp(buf, TRL1, strlen(TRL1))) {
        fprintf(stderr, "wrong data read (6)\n");
        fprintf(stderr, "received: `%.*s'\nexpected: `%s'\n",
                (int)bytes_read, buf, TRL1);
        exit(1);
    }
        
    assert(sizeof buf > strlen(TRL2));
    bytes_read = strlen(TRL2);
    rv = apr_socket_recv(newsock, buf, &bytes_read);
    if (rv != APR_SUCCESS) {
        aprerr("apr_socket_recv()", rv);
    }
    if (bytes_read != strlen(TRL2)) {
        fprintf(stderr, "wrong data read (7)\n");
        exit(1);
    }
    if (memcmp(buf, TRL2, strlen(TRL2))) {
        fprintf(stderr, "wrong data read (8)\n");
        fprintf(stderr, "received: `%.*s'\nexpected: `%s'\n",
                (int)bytes_read, buf, TRL2);
        exit(1);
    }

    for (i = 0; i < TRL3_LEN; i++) {
        bytes_read = 1;
        rv = apr_socket_recv(newsock, buf, &bytes_read);
        if (rv != APR_SUCCESS) {
            aprerr("apr_socket_recv()", rv);
        }
        if (bytes_read != 1) {
            fprintf(stderr, "apr_socket_recv()->%ld bytes instead of 1\n",
                    (long int)bytes_read);
            exit(1);
        }
        if (buf[0] != TRL3_CHAR) {
            fprintf(stderr,
                    "problem with data read (byte %d of trl 3):\n",
                    i);
            fprintf(stderr, "read `%c' (0x%x) from client; expected "
                    "`%c'\n",
                    buf[0], buf[0], TRL3_CHAR);
            exit(1);
        }
    }
        
    bytes_read = 1;
    rv = apr_socket_recv(newsock, buf, &bytes_read);
    if (rv != APR_EOF) {
        aprerr("apr_socket_recv() (expected APR_EOF)", rv);
    }
    if (bytes_read != 0) {
        fprintf(stderr, "We expected to get 0 bytes read with APR_EOF\n"
                "but instead we read %ld bytes (%c).\n",
                (long int)bytes_read, buf[0]);
        exit(1);
    }

    printf("server: apr_socket_sendfile() worked as expected!\n");

    return 0;
}