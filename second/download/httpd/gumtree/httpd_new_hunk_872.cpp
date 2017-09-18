            if (nvec_trailers) {
                hdtr.numtrailers = nvec_trailers;
                hdtr.trailers = vec_trailers;
            }

#if APR_HAS_SENDFILE
            if (apr_file_flags_get(fd) & APR_SENDFILE_ENABLED) {

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
                                                       headers              */
                                     &bytes_sent,   /* how many bytes were
                                                       sent                 */
                                     flags);   /* apr_sendfile flags        */

                if (logio_add_bytes_out && bytes_sent > 0)
                    logio_add_bytes_out(c, bytes_sent);
            }
            else
#endif
            {
                rv = emulate_sendfile(net, fd, &hdtr, foffset, flen,
                                      &bytes_sent);

                if (logio_add_bytes_out && bytes_sent > 0)
                    logio_add_bytes_out(c, bytes_sent);
            }

            fd = NULL;
        }
        else {
            apr_size_t bytes_sent;

            rv = writev_it_all(net->client_socket,
                               vec, nvec,
                               nbytes, &bytes_sent);

            if (logio_add_bytes_out && bytes_sent > 0)
                logio_add_bytes_out(c, bytes_sent);
        }

        apr_brigade_destroy(b);
        
        /* drive cleanups for resources which were set aside 
         * this may occur before or after termination of the request which
         * created the resource
         */
        if (ctx->deferred_write_pool) {
            if (more && more->p == ctx->deferred_write_pool) {
                /* "more" belongs to the deferred_write_pool,
                 * which is about to be cleared.
                 */
                if (APR_BRIGADE_EMPTY(more)) {
                    more = NULL;
                }
                else {
                    /* uh oh... change more's lifetime 
                     * to the input brigade's lifetime 
                     */
                    apr_bucket_brigade *tmp_more = more;
                    more = NULL;
                    ap_save_brigade(f, &more, &tmp_more, input_pool);
                }
            }
            apr_pool_clear(ctx->deferred_write_pool);  
        }

        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
                         "core_output_filter: writing data to the network");

            if (more)
                apr_brigade_destroy(more);
