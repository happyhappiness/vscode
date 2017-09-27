        vec_next->iov_len = sizeof(CRLF) - 1;
        vec_next++;
        t_elt++;
    } while (t_elt < t_end);

    if (APLOGrtrace4(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                      "Headers sent to client:");
        t_elt = (const apr_table_entry_t *)(elts->elts);
        do {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r, "%s: %s",
                          ap_escape_logitem(r->pool, t_elt->key),
                          ap_escape_logitem(r->pool, t_elt->val));
            t_elt++;
        } while (t_elt < t_end);
    }

