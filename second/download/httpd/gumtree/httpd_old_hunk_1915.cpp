    }
    if (!ap_is_HTTP_INFO(r->status)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "Status is %d - not sending interim response", r->status);
        return;
    }

    /* if we send an interim response, we're no longer in a state of
     * expecting one.  Also, this could feasibly be in a subrequest,
     * so we need to propagate the fact that we responded.
     */
    for (rr = r; rr != NULL; rr = rr->main) {
