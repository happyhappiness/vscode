                    }
                    return rv;
                }
                /* remove the data we've just read */
                rv = apr_brigade_partition(bb, bytes, &bstart);
                while (b = APR_BRIGADE_FIRST(bb), b != bstart) {
                    APR_BUCKET_REMOVE(b);
                    apr_bucket_destroy(b);
                }
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r, APLOGNO(01438)
                              "xml2enc: consuming %" APR_SIZE_T_FMT
                              " bytes flattened", bytes);
            }
            else {
