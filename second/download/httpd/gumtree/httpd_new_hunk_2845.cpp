    char *ret;
    int status;

    /* It may have changed since last time, so try again */

    if ((ret = try_alias_list(r, dirconf->redirects, 1, &status)) != NULL) {
        if (ret == PREGSUB_ERROR)
            return HTTP_INTERNAL_SERVER_ERROR;
        if (ap_is_HTTP_REDIRECT(status)) {
            if (ret[0] == '/') {
                char *orig_target = ret;

                ret = ap_construct_url(r->pool, ret, r);
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00675)
                              "incomplete redirection target of '%s' for "
                              "URI '%s' modified to '%s'",
                              orig_target, r->uri, ret);
            }
            if (!ap_is_url(ret)) {
                status = HTTP_INTERNAL_SERVER_ERROR;
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00676)
                              "cannot redirect '%s' to '%s'; "
                              "target is not a valid absoluteURI or abs_path",
                              r->uri, ret);
            }
            else {
                /* append requested query only, if the config didn't
