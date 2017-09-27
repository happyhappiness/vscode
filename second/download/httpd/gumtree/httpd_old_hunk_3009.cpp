                        clen -= readbuflen;
                        goto recv_again;
                    }
                } else {
                    /* XXX what if we haven't seen end of the headers yet? */

                    b = apr_bucket_eos_create(c->bucket_alloc);

                    APR_BRIGADE_INSERT_TAIL(ob, b);

                    rv = ap_pass_brigade(r->output_filters, ob);
                    if (rv != APR_SUCCESS) {
                        break;
                    }

                    /* XXX Why don't we cleanup here?  (logic from AJP) */
                }
                break;

            case FCGI_STDERR:
                /* TODO: Should probably clean up this logging a bit... */
                if (clen) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                                 "proxy: FCGI: Got error '%s'", readbuf);
                }

                if (clen > readbuflen) {
                    clen -= readbuflen;
                    goto recv_again;
                }
