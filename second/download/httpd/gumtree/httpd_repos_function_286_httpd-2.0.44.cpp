dav_error *dav_auto_checkout(
    request_rec *r,
    dav_resource *resource,
    int parent_only,
    dav_auto_version_info *av_info)
{
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    dav_lockdb *lockdb = NULL;
    dav_error *err = NULL;

    /* Initialize results */
    memset(av_info, 0, sizeof(*av_info));

    /* if no versioning provider, just return */
    if (vsn_hooks == NULL)
        return NULL;

    /* check parent resource if requested or if resource must be created */
    if (!resource->exists || parent_only) {
        dav_resource *parent;

        if ((err = (*resource->hooks->get_parent_resource)(resource,
                                                           &parent)) != NULL)
            goto done;

        if (parent == NULL || !parent->exists) {
            err = dav_new_error(r->pool, HTTP_CONFLICT, 0,
                                apr_psprintf(r->pool,
                                            "Missing one or more intermediate "
                                            "collections. Cannot create resource %s.",
                                            ap_escape_html(r->pool, resource->uri)));
            goto done;
        }

        av_info->parent_resource = parent;

        /* if parent versioned and not checked out, see if it can be */
        if (parent->versioned && !parent->working) {
            int checkout_parent;

            if ((err = dav_can_auto_checkout(r, parent,
                                             (*vsn_hooks->auto_versionable)(parent),
                                             &lockdb, &checkout_parent))
                != NULL) {
                goto done;
            }

            if (!checkout_parent) {
                err = dav_new_error(r->pool, HTTP_CONFLICT, 0,
                                    "<DAV:cannot-modify-checked-in-parent>");
                goto done;
            }

            /* Try to checkout the parent collection.
             * Note that auto-versioning can only be applied to a version selector,
             * so no separate working resource will be created.
             */
            if ((err = (*vsn_hooks->checkout)(parent, 1 /*auto_checkout*/,
                                              0, 0, 0, NULL, NULL))
                != NULL)
            {
                err = dav_push_error(r->pool, HTTP_CONFLICT, 0,
                                     apr_psprintf(r->pool,
                                                 "Unable to auto-checkout parent collection. "
                                                 "Cannot create resource %s.",
                                                 ap_escape_html(r->pool, resource->uri)),
                                     err);
                goto done;
            }

            /* remember that parent was checked out */
            av_info->parent_checkedout = 1;
        }
    }

    /* if only checking parent, we're done */
    if (parent_only)
        goto done;

    /* if creating a new resource, see if it should be version-controlled */
    if (!resource->exists
        && (*vsn_hooks->auto_versionable)(resource) == DAV_AUTO_VERSION_ALWAYS) {

        if ((err = (*vsn_hooks->vsn_control)(resource, NULL)) != NULL) {
            err = dav_push_error(r->pool, HTTP_CONFLICT, 0,
                                 apr_psprintf(r->pool,
                                             "Unable to create versioned resource %s.",
                                             ap_escape_html(r->pool, resource->uri)),
                                 err);
            goto done;
        }

        /* remember that resource was created */
        av_info->resource_versioned = 1;
    }

    /* if resource is versioned, make sure it is checked out */
    if (resource->versioned && !resource->working) {
        int checkout_resource;

        if ((err = dav_can_auto_checkout(r, resource,
                                         (*vsn_hooks->auto_versionable)(resource),
                                         &lockdb, &checkout_resource)) != NULL) {
            goto done;
        }

        if (!checkout_resource) {
            err = dav_new_error(r->pool, HTTP_CONFLICT, 0,
                                "<DAV:cannot-modify-version-controlled-content>");
            goto done;
        }

        /* Auto-versioning can only be applied to version selectors, so
         * no separate working resource will be created. */
        if ((err = (*vsn_hooks->checkout)(resource, 1 /*auto_checkout*/,
                                          0, 0, 0, NULL, NULL))
            != NULL)
        {
            err = dav_push_error(r->pool, HTTP_CONFLICT, 0,
                                 apr_psprintf(r->pool,
                                             "Unable to checkout resource %s.",
                                             ap_escape_html(r->pool, resource->uri)),
                                 err);
            goto done;
        }

        /* remember that resource was checked out */
        av_info->resource_checkedout = 1;
    }

done:

    /* make sure lock database is closed */
    if (lockdb != NULL)
        (*lockdb->hooks->close_lockdb)(lockdb);

    /* if an error occurred, undo any auto-versioning operations already done */
    if (err != NULL) {
        dav_auto_checkin(r, resource, 1 /*undo*/, 0 /*unlock*/, av_info);
        return err;
    }

    return NULL;
}