static int dav_method_unlock(request_rec *r)
{
    dav_error *err;
    dav_resource *resource;
    const dav_hooks_locks *locks_hooks;
    int result;
    const char *const_locktoken_txt;
    char *locktoken_txt;
    dav_locktoken *locktoken = NULL;
    int resource_state;
    dav_response *multi_response;

    /* If no locks provider, decline the request */
    locks_hooks = DAV_GET_HOOKS_LOCKS(r);
    if (locks_hooks == NULL)
        return DECLINED;

    if ((const_locktoken_txt = apr_table_get(r->headers_in,
                                             "Lock-Token")) == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Unlock failed (%s):  "
                      "No Lock-Token specified in header", r->filename);
        return HTTP_BAD_REQUEST;
    }

    locktoken_txt = apr_pstrdup(r->pool, const_locktoken_txt);
    if (locktoken_txt[0] != '<') {
        /* ### should provide more specifics... */
        return HTTP_BAD_REQUEST;
    }
    locktoken_txt++;

    if (locktoken_txt[strlen(locktoken_txt) - 1] != '>') {
        /* ### should provide more specifics... */
        return HTTP_BAD_REQUEST;
    }
    locktoken_txt[strlen(locktoken_txt) - 1] = '\0';

    if ((err = (*locks_hooks->parse_locktoken)(r->pool, locktoken_txt,
                                               &locktoken)) != NULL) {
        err = dav_push_error(r->pool, HTTP_BAD_REQUEST, 0,
                             apr_psprintf(r->pool,
                                          "The UNLOCK on %s failed -- an "
                                          "invalid lock token was specified "
                                          "in the \"If:\" header.",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, NULL);
    }

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    resource_state = dav_get_resource_state(r, resource);

    /*
     * Check If-Headers and existing locks.
     *
     * Note: depth == 0 normally requires no multistatus response. However,
     * if we pass DAV_VALIDATE_PARENT, then we could get an error on a URI
     * other than the Request-URI, thereby requiring a multistatus.
     *
     * If the resource is a locknull resource, then the UNLOCK will affect
     * the parent collection (much like a delete). For that case, we must
     * validate the parent resource's conditions.
     */
    if ((err = dav_validate_request(r, resource, 0, locktoken,
                                    &multi_response,
                                    resource_state == DAV_RESOURCE_LOCK_NULL
                                    ? DAV_VALIDATE_PARENT
                                    : DAV_VALIDATE_RESOURCE, NULL)) != NULL) {
        /* ### add a higher-level description? */
        return dav_handle_err(r, err, multi_response);
    }

    /* ### RFC 2518 s. 8.11: If this resource is locked by locktoken,
     *     _all_ resources locked by locktoken are released.  It does not say
     *     resource has to be the root of an infinte lock.  Thus, an UNLOCK
     *     on any part of an infinte lock will remove the lock on all resources.
     *
     *     For us, if r->filename represents an indirect lock (part of an infinity lock),
     *     we must actually perform an UNLOCK on the direct lock for this resource.
     */
    if ((result = dav_unlock(r, resource, locktoken)) != OK) {
        return result;
    }

    return HTTP_NO_CONTENT;
}