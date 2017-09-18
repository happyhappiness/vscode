
    /* We are not using multiviews */
    neg->count_multiviews_variants = 0;

    map = ap_pfopen(neg->pool, rr->filename, "r");
    if (map == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
                    "cannot access type map file: %s", rr->filename);
        return HTTP_FORBIDDEN;
    }

    clean_var_rec(&mime_info);

