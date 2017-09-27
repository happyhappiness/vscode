                    /* make sure we always clean up after ourselves */
                    apr_brigade_cleanup(bb);
                    apr_brigade_cleanup(pass_bb);

                } while (!finish);
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: end body send");
        }
        else if (!interim_response) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: header only");

            /* Pass EOS bucket down the filter chain. */
            e = apr_bucket_eos_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
            if (ap_pass_brigade(r->output_filters, bb) != APR_SUCCESS
