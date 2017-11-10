static int client(client_socket_mode_t socket_mode, char *host)
{
    apr_status_t rv, tmprv;
    apr_socket_t *sock;
    apr_pool_t *p;
    char buf[120];
    apr_file_t *f = NULL;
    apr_size_t len;
    apr_size_t expected_len;
    apr_off_t current_file_offset;
    apr_hdtr_t hdtr;
    struct iovec headers[3];
    struct iovec trailers[3];
    apr_size_t bytes_read;
    apr_pollset_t *pset;
    apr_int32_t nsocks;
    int i;
    int family;
    apr_sockaddr_t *destsa;

    family = APR_INET;
    apr_setup(&p, &sock, &family);
    create_testfile(p, TESTFILE);

    rv = apr_file_open(&f, TESTFILE, APR_READ, 0, p);
    if (rv != APR_SUCCESS) {
        fprintf(stderr, "apr_file_open()->%d/%s\n",
                rv,
                apr_strerror(rv, buf, sizeof buf));
        exit(1);
    }

    if (!host) {
        host = "127.0.0.1";
    }
    rv = apr_sockaddr_info_get(&destsa, host, family, TESTSF_PORT, 0, p);
    if (rv != APR_SUCCESS) {
        fprintf(stderr, "apr_sockaddr_info_get()->%d/%s\n",
                rv,
                apr_strerror(rv, buf, sizeof buf));
        exit(1);
    }

    rv = apr_socket_connect(sock, destsa);
    if (rv != APR_SUCCESS) {
        fprintf(stderr, "apr_socket_connect()->%d/%s\n", 
                rv,
		apr_strerror(rv, buf, sizeof buf));
        exit(1);
    }

    switch(socket_mode) {
    case BLK:
        /* leave it blocking */
        break;
    case NONBLK:
        /* set it non-blocking */
        rv = apr_socket_opt_set(sock, APR_SO_NONBLOCK, 1);
        if (rv != APR_SUCCESS) {
            fprintf(stderr, "apr_socket_opt_set(APR_SO_NONBLOCK)->%d/%s\n", 
                    rv,
                    apr_strerror(rv, buf, sizeof buf));
            exit(1);
        }
        break;
    case TIMEOUT:
        /* set a timeout */
        rv = apr_socket_timeout_set(sock, 100 * APR_USEC_PER_SEC);
        if (rv != APR_SUCCESS) {
            fprintf(stderr, "apr_socket_opt_set(APR_SO_NONBLOCK)->%d/%s\n", 
                    rv,
                    apr_strerror(rv, buf, sizeof buf));
            exit(1);
        }
        break;
    default:
        assert(1 != 1);
    }

    printf("Sending the file...\n");

    hdtr.headers = headers;
    hdtr.numheaders = 3;
    hdtr.headers[0].iov_base = HDR1;
    hdtr.headers[0].iov_len  = strlen(hdtr.headers[0].iov_base);
    hdtr.headers[1].iov_base = HDR2;
    hdtr.headers[1].iov_len  = strlen(hdtr.headers[1].iov_base);
    hdtr.headers[2].iov_base = malloc(HDR3_LEN);
    assert(hdtr.headers[2].iov_base);
    memset(hdtr.headers[2].iov_base, HDR3_CHAR, HDR3_LEN);
    hdtr.headers[2].iov_len  = HDR3_LEN;

    hdtr.trailers = trailers;
    hdtr.numtrailers = 3;
    hdtr.trailers[0].iov_base = TRL1;
    hdtr.trailers[0].iov_len  = strlen(hdtr.trailers[0].iov_base);
    hdtr.trailers[1].iov_base = TRL2;
    hdtr.trailers[1].iov_len  = strlen(hdtr.trailers[1].iov_base);
    hdtr.trailers[2].iov_base = malloc(TRL3_LEN);
    memset(hdtr.trailers[2].iov_base, TRL3_CHAR, TRL3_LEN);
    assert(hdtr.trailers[2].iov_base);
    hdtr.trailers[2].iov_len  = TRL3_LEN;

    expected_len = 
        strlen(HDR1) + strlen(HDR2) + HDR3_LEN +
        strlen(TRL1) + strlen(TRL2) + TRL3_LEN +
        FILE_LENGTH;
    
    if (socket_mode == BLK) {
        current_file_offset = 0;
        len = FILE_LENGTH;
        rv = apr_socket_sendfile(sock, f, &hdtr, &current_file_offset, &len, 0);
        if (rv != APR_SUCCESS) {
            fprintf(stderr, "apr_socket_sendfile()->%d/%s\n",
                    rv,
                    apr_strerror(rv, buf, sizeof buf));
            exit(1);
        }
        
        printf("apr_socket_sendfile() updated offset with %ld\n",
               (long int)current_file_offset);
        
        printf("apr_socket_sendfile() updated len with %ld\n",
               (long int)len);
        
        printf("bytes really sent: %" APR_SIZE_T_FMT "\n",
               expected_len);

        if (len != expected_len) {
            fprintf(stderr, "apr_socket_sendfile() didn't report the correct "
                    "number of bytes sent!\n");
            exit(1);
        }
    }
    else {
        /* non-blocking... wooooooo */
        apr_size_t total_bytes_sent;
        apr_pollfd_t pfd;

        pset = NULL;
        rv = apr_pollset_create(&pset, 1, p, 0);
        assert(!rv);
        pfd.p = p;
        pfd.desc_type = APR_POLL_SOCKET;
        pfd.reqevents = APR_POLLOUT;
        pfd.rtnevents = 0;
        pfd.desc.s = sock;
        pfd.client_data = NULL;

        rv = apr_pollset_add(pset, &pfd);        
        assert(!rv);

        total_bytes_sent = 0;
        current_file_offset = 0;
        len = FILE_LENGTH;
        do {
            apr_size_t tmplen;

            tmplen = len; /* bytes remaining to send from the file */
            printf("Calling apr_socket_sendfile()...\n");
            printf("Headers (%d):\n", hdtr.numheaders);
            for (i = 0; i < hdtr.numheaders; i++) {
                printf("\t%ld bytes (%c)\n",
                       (long)hdtr.headers[i].iov_len,
                       *(char *)hdtr.headers[i].iov_base);
            }
            printf("File: %ld bytes from offset %ld\n",
                   (long)tmplen, (long)current_file_offset);
            printf("Trailers (%d):\n", hdtr.numtrailers);
            for (i = 0; i < hdtr.numtrailers; i++) {
                printf("\t%ld bytes\n",
                       (long)hdtr.trailers[i].iov_len);
            }

            rv = apr_socket_sendfile(sock, f, &hdtr, &current_file_offset, &tmplen, 0);
            printf("apr_socket_sendfile()->%d, sent %ld bytes\n", rv, (long)tmplen);
            if (rv) {
                if (APR_STATUS_IS_EAGAIN(rv)) {
                    assert(tmplen == 0);
                    nsocks = 1;
                    tmprv = apr_pollset_poll(pset, -1, &nsocks, NULL);
                    assert(!tmprv);
                    assert(nsocks == 1);
                    /* continue; */
                }
            }

            total_bytes_sent += tmplen;

            /* Adjust hdtr to compensate for partially-written
             * data.
             */

            /* First, skip over any header data which might have
             * been written.
             */
            while (tmplen && hdtr.numheaders) {
                if (tmplen >= hdtr.headers[0].iov_len) {
                    tmplen -= hdtr.headers[0].iov_len;
                    --hdtr.numheaders;
                    ++hdtr.headers;
                }
                else {
                    hdtr.headers[0].iov_len -= tmplen;
                    hdtr.headers[0].iov_base = 
			(char*) hdtr.headers[0].iov_base + tmplen;
                    tmplen = 0;
                }
            }

            /* Now, skip over any file data which might have been
             * written.
             */

            if (tmplen <= len) {
                current_file_offset += tmplen;
                len -= tmplen;
                tmplen = 0;
            }
            else {
                tmplen -= len;
                len = 0;
                current_file_offset = 0;
            }

            /* Last, skip over any trailer data which might have
             * been written.
             */

            while (tmplen && hdtr.numtrailers) {
                if (tmplen >= hdtr.trailers[0].iov_len) {
                    tmplen -= hdtr.trailers[0].iov_len;
                    --hdtr.numtrailers;
                    ++hdtr.trailers;
                }
                else {
                    hdtr.trailers[0].iov_len -= tmplen;
                    hdtr.trailers[0].iov_base = 
			(char *)hdtr.trailers[0].iov_base + tmplen;
                    tmplen = 0;
                }
            }

        } while (total_bytes_sent < expected_len &&
                 (rv == APR_SUCCESS || 
                 (APR_STATUS_IS_EAGAIN(rv) && socket_mode != TIMEOUT)));
        if (total_bytes_sent != expected_len) {
            fprintf(stderr,
                    "client problem: sent %ld of %ld bytes\n",
                    (long)total_bytes_sent, (long)expected_len);
            exit(1);
        }

        if (rv) {
            fprintf(