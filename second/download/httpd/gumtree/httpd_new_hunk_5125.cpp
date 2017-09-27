        fprintf(stderr, "only simple translation is supported (%d/%"
                        APR_SIZE_T_FMT "/%" APR_SIZE_T_FMT ")\n",
                        status, inbytes_left, outbytes_left);
        exit(1);
    }
#endif              /* NOT_ASCII */

    if (myhost) {
        /* This only needs to be done once */
        if ((rv = apr_sockaddr_info_get(&mysa, myhost, APR_UNSPEC, 0, 0, cntxt)) != APR_SUCCESS) {
            char buf[120];
            apr_snprintf(buf, sizeof(buf),
                         "apr_sockaddr_info_get() for %s", myhost);
            apr_err(buf, rv);
        }
    }

    /* This too */
    if ((rv = apr_sockaddr_info_get(&destsa, connecthost,
                                    myhost ? mysa->family : APR_UNSPEC,
                                    connectport, 0, cntxt))
       != APR_SUCCESS) {
        char buf[120];
        apr_snprintf(buf, sizeof(buf),
                 "apr_sockaddr_info_get() for %s", connecthost);
