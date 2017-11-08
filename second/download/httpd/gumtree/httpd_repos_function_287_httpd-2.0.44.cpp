dav_error *dav_auto_checkin(
    request_rec *r,
    dav_resource *resource,
    int undo,
    int unlock,
    dav_auto_version_info *av_info)
{
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    dav_error *err = NULL;
    dav_auto_version auto_version;

    /* If no versioning provider, this is a no-op */
    if (vsn_hooks == NULL)
        return NULL;

    /* If undoing auto-checkouts, then do uncheckouts */
    if (undo) {
        if (resource != NULL) {
            if (av_info->resource_checkedout) {
                if ((err = (*vsn_hooks->uncheckout)(resource)) != NULL) {
                    return dav_push_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                                          apr_psprintf(r->pool,
                                                      "Unable to undo auto-checkout "
                                                      "of resource %s.",
                                                      ap_escape_html(r->pool, resource->uri)),
                                          err);
                }
            }

            if (av_info->resource_versioned) {
                dav_response *response;

                /* ### should we do anything with the response? */
                if ((err = (*resource->hooks->remove_resource)(resource,
                                                               &response)) != NULL) {
                    return dav_push_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                                          apr_psprintf(r->pool,
                                                      "Unable to undo auto-version-control "
                                                      "of resource %s.",
                                                      ap_escape_html(r->pool, resource->uri)),
                                          err);
                }
            }
        }

        if (av_info->parent_resource != NULL && av_info->parent_checkedout) {
            if ((err = (*vsn_hooks->uncheckout)(av_info->parent_resource)) != NULL) {
                return dav_push_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                                      apr_psprintf(r->pool,
                                                  "Unable to undo auto-checkout "
                                                  "of parent collection %s.",
                                                  ap_escape_html(r->pool, av_info->parent_resource->uri)),
                                      err);
            }
        }

        return NULL;
    }

    /* If the resource was checked out, and auto-checkin is enabled,
     * then check it in.
     */
    if (resource != NULL && resource->working
        && (unlock || av_info->resource_checkedout)) {

        auto_version = (*vsn_hooks->auto_versionable)(resource);

        if (auto_version == DAV_AUTO_VERSION_ALWAYS ||
            (unlock && (auto_version == DAV_AUTO_VERSION_LOCKED))) {

            if ((err = (*vsn_hooks->checkin)(resource,
                                             0 /*keep_checked_out*/, NULL))
                != NULL) {
                return dav_push_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                                      apr_psprintf(r->pool,
                                                  "Unable to auto-checkin resource %s.",
                                                  ap_escape_html(r->pool, resource->uri)),
                                      err);
            }
        }
    }

    /* If parent resource was checked out, and auto-checkin is enabled,
     * then check it in.
     */
    if (!unlock
        && av_info->parent_checkedout
        && av_info->parent_resource != NULL
        && av_info->parent_resource->working) {

        auto_version = (*vsn_hooks->auto_versionable)(av_info->parent_resource);

        if (auto_version == DAV_AUTO_VERSION_ALWAYS) {
            if ((err = (*vsn_hooks->checkin)(av_info->parent_resource,
                                             0 /*keep_checked_out*/, NULL))
                != NULL) {
                return dav_push_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                                      apr_psprintf(r->pool,
                                                  "Unable to auto-checkin parent collection %s.",
                                                  ap_escape_html(r->pool, av_info->parent_resource->uri)),
                                                  err);
            }
        }
    }

    return NULL;
}