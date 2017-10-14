static int dav_handler(request_rec *r)
{
    if (strcmp(r->handler, DAV_HANDLER_NAME) != 0)
        return DECLINED;

    /* Reject requests with an unescaped hash character, as these may
     * be more destructive than the user intended. */
    if (r->parsed_uri.fragment != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                     "buggy client used un-escaped hash in Request-URI");
        return dav_error_response(r, HTTP_BAD_REQUEST, 
                                  "The request was invalid: the URI included "
                                  "an un-escaped hash character");
    }

    /* ### do we need to do anything with r->proxyreq ?? */

    /*
     * ### anything else to do here? could another module and/or
     * ### config option "take over" the handler here? i.e. how do
     * ### we lock down this hierarchy so that we are the ultimate
     * ### arbiter? (or do we simply depend on the administrator
     * ### to avoid conflicting configurations?)
     */

    /*
     * Set up the methods mask, since that's one of the reasons this handler
     * gets called, and lower-level things may need the info.
     *
     * First, set the mask to the methods we handle directly.  Since by
     * definition we own our managed space, we unconditionally set
     * the r->allowed field rather than ORing our values with anything
     * any other module may have put in there.
     *
     * These are the HTTP-defined methods that we handle directly.
     */
    r->allowed = 0
        | (AP_METHOD_BIT << M_GET)
        | (AP_METHOD_BIT << M_PUT)
        | (AP_METHOD_BIT << M_DELETE)
        | (AP_METHOD_BIT << M_OPTIONS)
        | (AP_METHOD_BIT << M_INVALID);

    /*
     * These are the DAV methods we handle.
     */
    r->allowed |= 0
        | (AP_METHOD_BIT << M_COPY)
        | (AP_METHOD_BIT << M_LOCK)
        | (AP_METHOD_BIT << M_UNLOCK)
        | (AP_METHOD_BIT << M_MKCOL)
        | (AP_METHOD_BIT << M_MOVE)
        | (AP_METHOD_BIT << M_PROPFIND)
        | (AP_METHOD_BIT << M_PROPPATCH);

    /*
     * These are methods that we don't handle directly, but let the
     * server's default handler do for us as our agent.
     */
    r->allowed |= 0
        | (AP_METHOD_BIT << M_POST);

    /* ### hrm. if we return HTTP_METHOD_NOT_ALLOWED, then an Allow header
     * ### is sent; it will need the other allowed states; since the default
     * ### handler is not called on error, then it doesn't add the other
     * ### allowed states, so we must
     */

    /* ### we might need to refine this for just where we return the error.
     * ### also, there is the issue with other methods (see ISSUES)
     */

    /* dispatch the appropriate method handler */
    if (r->method_number == M_GET) {
        return dav_method_get(r);
    }

    if (r->method_number == M_PUT) {
        return dav_method_put(r);
    }

    if (r->method_number == M_POST) {
        return dav_method_post(r);
    }

    if (r->method_number == M_DELETE) {
        return dav_method_delete(r);
    }

    if (r->method_number == M_OPTIONS) {
        return dav_method_options(r);
    }

    if (r->method_number == M_PROPFIND) {
        return dav_method_propfind(r);
    }

    if (r->method_number == M_PROPPATCH) {
        return dav_method_proppatch(r);
    }

    if (r->method_number == M_MKCOL) {
        return dav_method_mkcol(r);
    }

    if (r->method_number == M_COPY) {
        return dav_method_copymove(r, DAV_DO_COPY);
    }

    if (r->method_number == M_MOVE) {
        return dav_method_copymove(r, DAV_DO_MOVE);
    }

    if (r->method_number == M_LOCK) {
        return dav_method_lock(r);
    }

    if (r->method_number == M_UNLOCK) {
        return dav_method_unlock(r);
    }

    if (r->method_number == M_VERSION_CONTROL) {
        return dav_method_vsn_control(r);
    }

    if (r->method_number == M_CHECKOUT) {
        return dav_method_checkout(r);
    }

    if (r->method_number == M_UNCHECKOUT) {
        return dav_method_uncheckout(r);
    }

    if (r->method_number == M_CHECKIN) {
        return dav_method_checkin(r);
    }

    if (r->method_number == M_UPDATE) {
        return dav_method_update(r);
    }

    if (r->method_number == M_LABEL) {
        return dav_method_label(r);
    }

    if (r->method_number == M_REPORT) {
        return dav_method_report(r);
    }

    if (r->method_number == M_MKWORKSPACE) {
        return dav_method_make_workspace(r);
    }

    if (r->method_number == M_MKACTIVITY) {
        return dav_method_make_activity(r);
    }

    if (r->method_number == M_BASELINE_CONTROL) {
        return dav_method_baseline_control(r);
    }

    if (r->method_number == M_MERGE) {
        return dav_method_merge(r);
    }

    /* BIND method */
    if (r->method_number == dav_methods[DAV_M_BIND]) {
        return dav_method_bind(r);
    }

    /* DASL method */
    if (r->method_number == dav_methods[DAV_M_SEARCH]) {
        return dav_method_search(r);
    }

    /* ### add'l methods for Advanced Collections, ACLs */

    return DECLINED;
}