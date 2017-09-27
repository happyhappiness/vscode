            next = APR_BUCKET_NEXT(b);
            if (H2_BUCKET_IS_HEADERS(b)) {
                h2_headers *headers = h2_bucket_headers_get(b);
                ap_assert(headers);
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "h2_task(%s): receiving trailers", task->id);
                r->trailers_in = apr_table_clone(r->pool, headers->headers);
                APR_BUCKET_REMOVE(b);
                apr_bucket_destroy(b);
                ap_remove_input_filter(f);
                break;
            }
        }
