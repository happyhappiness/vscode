            if (nvec_trailers) {
                hdtr.numtrailers = nvec_trailers;
                hdtr.trailers = vec_trailers;
            }

#if APR_HAS_SENDFILE
            if (c->keepalive == AP_CONN_CLOSE && APR_BUCKET_IS_EOS(last_e)) {
                /* Prepare the socket to be reused */
                flags |= APR_SENDFILE_DISCONNECT_SOCKET;
            }

            rv = sendfile_it_all(net,      /* the network information   */
                                 fd,       /* the file to send          */
                                 &hdtr,    /* header and trailer iovecs */
                                 foffset,  /* offset in the file to begin
                                              sending from              */
                                 flen,     /* length of file            */
                                 nbytes + flen, /* total length including
                                                   headers                */
                                 flags);   /* apr_sendfile flags        */

            /* If apr_sendfile() returns APR_ENOTIMPL, call emulate_sendfile().
             * emulate_sendfile() is useful to enable the same Apache binary
             * distribution to support Windows NT/2000 (supports TransmitFile)
             * and Win95/98 (do not support TransmitFile)
             */
            if (rv == APR_ENOTIMPL)
#endif
            {
                apr_size_t unused_bytes_sent;
                rv = emulate_sendfile(net, fd, &hdtr, foffset, flen,
                                      &unused_bytes_sent);
            }

            fd = NULL;
        }
        else {
            apr_size_t unused_bytes_sent;

            rv = writev_it_all(net->client_socket,
                               vec, nvec,
                               nbytes, &unused_bytes_sent);
        }

        apr_brigade_destroy(b);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
                         "core_output_filter: writing data to the network");

            if (more)
                apr_brigade_destroy(more);
