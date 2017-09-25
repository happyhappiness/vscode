
    lookup = dav_lookup_uri(dest, r, 0 /* must_be_absolute */);
    if (lookup.rnew == NULL) {
        if (lookup.err.status == HTTP_BAD_REQUEST) {
            /* This supplies additional information for the default message. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "%s", lookup.err.desc);
            return HTTP_BAD_REQUEST;
        }
        else if (lookup.err.status == HTTP_BAD_GATEWAY) {
            /* ### Bindings protocol draft 02 says to return 507
             * ### (Cross Server Binding Forbidden); Apache already defines 507
             * ### as HTTP_INSUFFICIENT_STORAGE. So, for now, we'll return
