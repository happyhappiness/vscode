    if ((ret = try_alias_list(r, serverconf->redirects, 1, &status)) != NULL) {
        if (ap_is_HTTP_REDIRECT(status)) {
            char *orig_target = ret;
            if (ret[0] == '/') {

                ret = ap_construct_url(r->pool, ret, r);
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                              "incomplete redirection target of '%s' for "
                              "URI '%s' modified to '%s'",
                              orig_target, r->uri, ret);
            }
            if (!ap_is_url(ret)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
