
#ifdef NOT_ASCII
    inbytes_left = outbytes_left = reqlen;
    status = apr_xlate_conv_buffer(to_ascii, request, &inbytes_left,
                   request, &outbytes_left);
    if (status || inbytes_left || outbytes_left) {
        fprintf(stderr, "only simple translation is supported (%d/%"
                        APR_SIZE_T_FMT "/%" APR_SIZE_T_FMT ")\n",
                        status, inbytes_left, outbytes_left);
        exit(1);
    }
#endif              /* NOT_ASCII */

    /* This only needs to be done once */
    if ((rv = apr_sockaddr_info_get(&destsa, connecthost, APR_UNSPEC, connectport, 0, cntxt))
