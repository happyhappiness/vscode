static int dav_method_lock(request_rec *r)
{
    dav_error *err;
    dav_resource *resource;
    dav_resource *parent;
    const dav_hooks_locks *locks_hooks;
    int result;
    int depth;
    int new_lock_request = 0;
    apr_xml_doc *doc;
    dav_lock *lock;
    dav_response *multi_response = NULL;
    dav_lockdb *lockdb;
    int resource_state;

    /* If no locks provider, decline the request */
    locks_hooks = DAV_GET_HOOKS_LOCKS(r);
    if (locks_hooks == NULL)
        return DECLINED;

    if ((result = ap_xml_parse_input(r, &doc)) != OK)
        return result;

    depth = dav_get_depth(r, DAV_INFINITY);
    if (depth != 0 && depth != DAV_INFINITY) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Depth must be 0 or \"infinity\" for LOCK.");
        return HTTP_BAD_REQUEST;
    }

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    /* Check if parent collection exists */
    if ((err = resource->hooks->get_parent_resource(resource, &parent)) != NULL) {
        /* ### add a higher-level description? */
        return dav_handle_err(r, err, NULL);
    }
    if (parent && (!parent->exists || parent->collection != 1)) {
        err = dav_new_error(r->pool, HTTP_CONFLICT, 0, 0,
                           apr_psprintf(r->pool,
                                        "The parent resource of %s does not "
                                        "exist or is not a collection.", 
                                        ap_escape_html(r->pool, r->uri)));
        return dav_handle_err(r, err, NULL);
    }

    /*
     * Open writable. Unless an error occurs, we'll be
     * writing into the database.
     */
    if ((err = (*locks_hooks->open_lockdb)(r, 0, 0, &lockdb)) != NULL) {
        /* ### add a higher-level description? */
        return dav_handle_err(r, err, NULL);
    }

    if (doc != NULL) {
        if ((err = dav_lock_parse_lockinfo(r, resource, lockdb, doc,
                                               &lock)) != NULL) {
            /* ### add a higher-level description to err? */
            goto error;
        }
        new_lock_request = 1;

        lock->auth_user = apr_pstrdup(r->pool, r->user);
    }

    resource_state = dav_get_resource_state(r, resource);

    /*
     * Check If-Headers and existing locks.
     *
     * If this will create a locknull resource, then the LOCK will affect
     * the parent collection (much like a PUT/MKCOL). For that case, we must
     * validate the parent resource's conditions.
     */
    if ((err = dav_validate_request(r, resource, depth, NULL, &multi_response,
                                    (resource_state == DAV_RESOURCE_NULL
                                     ? DAV_VALIDATE_PARENT
                                     : DAV_VALIDATE_RESOURCE)
                                    | (new_lock_request ? lock->scope : 0)
                                    | DAV_VALIDATE_ADD_LD,
                                    lockdb)) != OK) {
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not LOCK %s due to a failed "
                                          "precondition (e.g. other locks).",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        goto error;
    }

    if (new_lock_request == 0) {
        dav_locktoken_list *ltl;

        /*
         * Refresh request
         * ### Assumption:  We can renew multiple locks on the same resource
         * ### at once. First harvest all the positive lock-tokens given in
         * ### the If header. Then modify the lock entries for this resource
         * ### with the new Timeout val.
         */

        if ((err = dav_get_locktoken_list(r, &ltl)) != NULL) {
            err = dav_push_error(r->pool, err->status, 0,
                                 apr_psprintf(r->pool,
                                              "The lock refresh for %s failed "
                                              "because no lock tokens were "
                                              "specified in an \"If:\" "
                                              "header.",
                                              ap_escape_html(r->pool, r->uri)),
                                 err);
            goto error;
        }

        if ((err = (*locks_hooks->refresh_locks)(lockdb, resource, ltl,
                                                 dav_get_timeout(r),
                                                 &lock)) != NULL) {
            /* ### add a higher-level description to err? */
            goto error;
        }
    } else {
        /* New lock request */
        char *locktoken_txt;
        dav_dir_conf *conf;

        conf = (dav_dir_conf *)ap_get_module_config(r->per_dir_config,
                                                    &dav_module);

        /* apply lower bound (if any) from DAVMinTimeout directive */
        if (lock->timeout != DAV_TIMEOUT_INFINITE
            && lock->timeout < time(NULL) + conf->locktimeout)
            lock->timeout = time(NULL) + conf->locktimeout;

        err = dav_add_lock(r, resource, lockdb, lock, &multi_response);
        if (err != NULL) {
            /* ### add a higher-level description to err? */
            goto error;
        }

        locktoken_txt = apr_pstrcat(r->pool, "<",
                                    (*locks_hooks->format_locktoken)(r->pool,
                                        lock->locktoken),
                                    ">", NULL);

        apr_table_set(r->headers_out, "Lock-Token", locktoken_txt);
    }

    (*locks_hooks->close_lockdb)(lockdb);

    r->status = HTTP_OK;
    ap_set_content_type(r, DAV_XML_CONTENT_TYPE);

    ap_rputs(DAV_XML_HEADER DEBUG_CR "<D:prop xmlns:D=\"DAV:\">" DEBUG_CR, r);
    if (lock == NULL)
        ap_rputs("<D:lockdiscovery/>" DEBUG_CR, r);
    else {
        ap_rprintf(r,
                   "<D:lockdiscovery>" DEBUG_CR
                   "%s" DEBUG_CR
                   "</D:lockdiscovery>" DEBUG_CR,
                   dav_lock_get_activelock(r, lock, NULL));
    }
    ap_rputs("</D:prop>", r);

    /* the response has been sent. */
    return DONE;

  error:
    (*locks_hooks->close_lockdb)(lockdb);
    return dav_handle_err(r, err, multi_response);
}