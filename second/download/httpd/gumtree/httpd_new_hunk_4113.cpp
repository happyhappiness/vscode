                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01056)
                             "proxy: readbytes: %#x", readbytes);
            }
#endif
            /* sanity check */
            if (APR_BRIGADE_EMPTY(bb)) {
                break;
            }

            /* found the last brigade? */
            if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
                /* if this is the last brigade, cleanup the
