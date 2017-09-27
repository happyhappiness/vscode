
                    if (script_error_status == HTTP_OK) {
                        b = apr_bucket_eos_create(c->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(ob, b);
                        rv = ap_pass_brigade(r->output_filters, ob);
                        if (rv != APR_SUCCESS) {
                            break;
                        }
                    }

                    /* XXX Why don't we cleanup here?  (logic from AJP) */
                }
                break;

            case AP_FCGI_STDERR:
                /* TODO: Should probably clean up this logging a bit... */
                if (clen) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01071)
                                  "Got error '%s'", readbuf);
                }

                if (clen > readbuflen) {
                    clen -= readbuflen;
                    goto recv_again;
                }
