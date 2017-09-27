                            apr_array_pstrcat(p, v, ','));

            apr_pool_destroy(sub_pool);

            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                         ref ? "Spelling fix: %s: %d candidates from %s"
                             : "Spelling fix: %s: %d candidates%s",
                         r->uri, candidates->nelts,
                         (ref ? ref : ""));

            return HTTP_MULTIPLE_CHOICES;
        }
    }

    return OK;
