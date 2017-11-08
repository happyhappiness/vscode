static int dav_method_mkcol(request_rec *r)
{
    dav_resource *resource;
    int resource_state;
    dav_auto_version_info av_info;
    const dav_hooks_locks *locks_hooks = DAV_GET_HOOKS_LOCKS(r);
    dav_error *err;
    dav_error *err2;
    int result;
    dav_dir_conf *conf;
    dav_response *multi_status;

    /* handle the request body */
    /* ### this may move lower once we start processing bodies */
    if ((result = process_mkcol_body(r)) != OK) {
        return result;
    }

    conf = (dav_dir_conf *)ap_get_module_config(r->per_dir_config,
                                                &dav_module);

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    if (resource->exists) {
        /* oops. something was already there! */

        /* Apache will supply a default error for this. */
        /* ### we should provide a specific error message! */
        return HTTP_METHOD_NOT_ALLOWED;
    }

    resource_state = dav_get_resource_state(r, resource);

    /*
     * Check If-Headers and existing locks.
     *
     * Note: depth == 0 normally requires no multistatus response. However,
     * if we pass DAV_VALIDATE_PARENT, then we could get an error on a URI
     * other than the Request-URI, thereby requiring a multistatus.
     *
     * If the resource does not exist (DAV_RESOURCE_NULL), then we must
     * check the resource *and* its parent. If the resource exists or is
     * a locknull resource, then we check only the resource.
     */
    if ((err = dav_validate_request(r, resource, 0, NULL, &multi_status,
                                    resource_state == DAV_RESOURCE_NULL ?
                                    DAV_VALIDATE_PARENT :
                                    DAV_VALIDATE_RESOURCE, NULL)) != NULL) {
        /* ### add a higher-level description? */
        return dav_handle_err(r, err, multi_status);
    }

    /* if versioned resource, make sure parent is checked out */
    if ((err = dav_auto_checkout(r, resource, 1 /* parent_only */,
                                 &av_info)) != NULL) {
        /* ### add a higher-level description? */
        return dav_handle_err(r, err, NULL);
    }

    /* try to create the collection */
    resource->collection = 1;
    err = (*resource->hooks->create_collection)(resource);

    /* restore modifiability of parent back to what it was */
    err2 = dav_auto_checkin(r, NULL, err != NULL /* undo if error */,
                            0 /*unlock*/, &av_info);

    /* check for errors now */
    if (err != NULL) {
        return dav_handle_err(r, err, NULL);
    }
    if (err2 != NULL) {
        /* just log a warning */
        err = dav_push_error(r->pool, err2->status, 0,
                             "The MKCOL was successful, but there "
                             "was a problem automatically checking in "
                             "the parent collection.",
                             err2);
        dav_log_err(r, err, APLOG_WARNING);
    }

    if (locks_hooks != NULL) {
        dav_lockdb *lockdb;

        if ((err = (*locks_hooks->open_lockdb)(r, 0, 0, &lockdb)) != NULL) {
            /* The directory creation was successful, but the locking failed. */
            err = dav_push_error(r->pool, err->status, 0,
                                 "The MKCOL was successful, but there "
                                 "was a problem opening the lock database "
                                 "which prevents inheriting locks from the "
                                 "parent resources.",
                                 err);
            return dav_handle_err(r, err, NULL);
        }

        /* notify lock system that we have created/replaced a resource */
        err = dav_notify_created(r, lockdb, resource, resource_state, 0);

        (*locks_hooks->close_lockdb)(lockdb);

        if (err != NULL) {
            /* The dir creation was successful, but the locking failed. */
            err = dav_push_error(r->pool, err->status, 0,
                                 "The MKCOL was successful, but there "
                                 "was a problem updating its lock "
                                 "information.",
                                 err);
            return dav_handle_err(r, err, NULL);
        }
    }

    /* return an appropriate response (HTTP_CREATED) */
    return dav_created(r, NULL, "Collection", 0);
}