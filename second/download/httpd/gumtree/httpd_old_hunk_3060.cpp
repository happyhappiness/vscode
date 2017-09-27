                    mode = APR_NONBLOCK_READ;

                    apr_brigade_length(bb, 0, &readbytes);
                    backend->worker->s->read += readbytes;
#if DEBUGGING
                    {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                                 r->server, "proxy (PID %d): readbytes: %#x",
                                 getpid(), readbytes);
                    }
#endif
                    /* sanity check */
                    if (APR_BRIGADE_EMPTY(bb)) {
                        apr_brigade_cleanup(bb);
                        break;
                    }

                    /* Switch the allocator lifetime of the buckets */
                    ap_proxy_buckets_lifetime_transform(r, bb, pass_bb);

                    /* found the last brigade? */
                    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
                        /* signal that we must leave */
                        finish = TRUE;
                    }

                    /* try send what we read */
                    if (ap_pass_brigade(r->output_filters, pass_bb) != APR_SUCCESS
                        || c->aborted) {
                        /* Ack! Phbtt! Die! User aborted! */
                        backend->close = 1;  /* this causes socket close below */
                        finish = TRUE;
                    }

                    /* make sure we always clean up after ourselves */
                    apr_brigade_cleanup(bb);
                    apr_brigade_cleanup(pass_bb);

                } while (!finish);
            }
            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
                         "proxy: end body send");
        }
        else if (!interim_response) {
            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
                         "proxy: header only");

            /* Pass EOS bucket down the filter chain. */
            e = apr_bucket_eos_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
            if (ap_pass_brigade(r->output_filters, bb) != APR_SUCCESS
                || c->aborted) {
                /* Ack! Phbtt! Die! User aborted! */
                backend->close = 1;  /* this causes socket close below */
            }

            apr_brigade_cleanup(bb);
        }
    } while (interim_response && (interim_response < AP_MAX_INTERIM_RESPONSES));

    /* See define of AP_MAX_INTERIM_RESPONSES for why */
    if (interim_response >= AP_MAX_INTERIM_RESPONSES) {
        return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                             apr_psprintf(p, 
                             "Too many (%d) interim responses from origin server",
                             interim_response));
    }

    /* If our connection with the client is to be aborted, return DONE. */
    if (c->aborted || backend_broke) {
