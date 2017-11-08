static void read_connection(struct connection * c)
{
    apr_size_t r;
    apr_status_t status;
    char *part;
    char respcode[4];       /* 3 digits and null */

    r = sizeof(buffer);
#ifdef USE_SSL
    if (c->ssl) {
        status = SSL_read(c->ssl, buffer, r);
        if (status <= 0) {
            int scode = SSL_get_error(c->ssl, status);

            if (scode == SSL_ERROR_ZERO_RETURN) {
                /* connection closed cleanly: */
                good++;
                close_connection(c);
            }
            else if (scode != SSL_ERROR_WANT_WRITE
                     && scode != SSL_ERROR_WANT_READ) {
                /* some fatal error: */
                c->read = 0;
                BIO_printf(bio_err, "SSL read failed - closing connection\n");
                ERR_print_errors(bio_err);
                close_connection(c);
            }
            return;
        }
        r = status;
    }
    else
#endif
    {
        status = apr_socket_recv(c->aprsock, buffer, &r);
        if (APR_STATUS_IS_EAGAIN(status))
            return;
        else if (r == 0 && APR_STATUS_IS_EOF(status)) {
            good++;
            close_connection(c);
            return;
        }
        /* catch legitimate fatal apr_socket_recv errors */
        else if (status != APR_SUCCESS) {
            err_except++; /* XXX: is this the right error counter? */
            /* XXX: Should errors here be fatal, or should we allow a
             * certain number of them before completely failing? -aaron */
            apr_err("apr_socket_recv", status);
        }
    }

    totalread += r;
    if (c->read == 0) {
        c->beginread = apr_time_now();
    }
    c->read += r;


    if (!c->gotheader) {
        char *s;
        int l = 4;
        apr_size_t space = CBUFFSIZE - c->cbx - 1; /* -1 allows for \0 term */
        int tocopy = (space < r) ? space : r;
#ifdef NOT_ASCII
        apr_size_t inbytes_left = space, outbytes_left = space;

        status = apr_xlate_conv_buffer(from_ascii, buffer, &inbytes_left,
                           c->cbuff + c->cbx, &outbytes_left);
        if (status || inbytes_left || outbytes_left) {
            fprintf(stderr, "only simple translation is supported (%d/%u/%u)\n",
                status, inbytes_left, outbytes_left);
            exit(1);
        }
#else
        memcpy(c->cbuff + c->cbx, buffer, space);
#endif              /* NOT_ASCII */
        c->cbx += tocopy;
        space -= tocopy;
        c->cbuff[c->cbx] = 0;   /* terminate for benefit of strstr */
        if (verbosity >= 2) {
            printf("LOG: header received:\n%s\n", c->cbuff);
        }
        s = strstr(c->cbuff, "\r\n\r\n");
        /*
         * this next line is so that we talk to NCSA 1.5 which blatantly
         * breaks the http specifaction
         */
        if (!s) {
            s = strstr(c->cbuff, "\n\n");
            l = 2;
        }

        if (!s) {
            /* read rest next time */
            if (space) {
                return;
            }
            else {
            /* header is in invalid or too big - close connection */
                apr_pollfd_t remove_pollfd;
                remove_pollfd.desc_type = APR_POLL_SOCKET;
                remove_pollfd.desc.s = c->aprsock;
                apr_pollset_remove(readbits, &remove_pollfd);
                apr_socket_close(c->aprsock);
                err_response++;
                if (bad++ > 10) {
                    err("\nTest aborted after 10 failures\n\n");
                }
                start_connect(c);
            }
        }
        else {
            /* have full header */
            if (!good) {
                /*
                 * this is first time, extract some interesting info
                 */
                char *p, *q;
                p = strstr(c->cbuff, "Server:");
                q = servername;
                if (p) {
                    p += 8;
                    while (*p > 32)
                    *q++ = *p++;
                }
                *q = 0;
            }
            /*
             * XXX: this