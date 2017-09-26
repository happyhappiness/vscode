#ifdef NOT_ASCII
        apr_size_t inbytes_left = space, outbytes_left = space;

        status = apr_xlate_conv_buffer(from_ascii, buffer, &inbytes_left,
                           c->cbuff + c->cbx, &outbytes_left);
        if (status || inbytes_left || outbytes_left) {
            fprintf(stderr, "only simple translation is supported (%d/%" APR_SIZE_T_FMT
                            "/%" APR_SIZE_T_FMT ")\n", status, inbytes_left, outbytes_left);
            exit(1);
        }
#else
        memcpy(c->cbuff + c->cbx, buffer, space);
#endif              /* NOT_ASCII */
        c->cbx += tocopy;
