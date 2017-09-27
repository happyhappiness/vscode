    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02450) "declining URL %s", url);
        return DECLINED;
    }

    if (ap_cstr_casecmp(upgrade_method, "NONE") != 0) {
        const char *upgrade;
        upgrade = apr_table_get(r->headers_in, "Upgrade");
        if (!upgrade || ap_cstr_casecmp(upgrade, upgrade_method) != 0) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02900)
                          "declining URL %s  (not %s, Upgrade: header is %s)", 
                          url, upgrade_method, upgrade ? upgrade : "missing");
            return DECLINED;
        }
    }

    uri = apr_palloc(p, sizeof(*uri));
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02451) "serving URL %s", url);

    /* create space for state information */
