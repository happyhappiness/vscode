                                                    readbuflen,
                                                    c->bucket_alloc);

                    APR_BRIGADE_INSERT_TAIL(ob, b);

                    if (! seen_end_of_headers) {
                        int st = handle_headers(r, &header_state, readbuf, ob);

                        if (st == 1) {
                            seen_end_of_headers = 1;

                            rv = ap_pass_brigade(r->output_filters, ob);
                            if (rv != APR_SUCCESS) {
                                break;
                            }

                            apr_brigade_cleanup(ob);

                            apr_pool_clear(setaside_pool);
                        }
                        else if (st == -1) {
                            rv = APR_EINVAL;
                            break;
                        }
                        else {
                            /* We're still looking for the end of the
                             * headers, so this part of the data will need
                             * to persist. */
                            apr_bucket_setaside(b, setaside_pool);
                        }
