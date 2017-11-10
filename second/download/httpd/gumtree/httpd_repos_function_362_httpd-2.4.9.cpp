static int dav_method_search(request_rec *r)
{
    const dav_hooks_search *search_hooks = DAV_GET_HOOKS_SEARCH(r);
    dav_resource *resource;
    dav_error *err;
    dav_response *multi_status;

    /* If no search provider, decline the request */
    if (search_hooks == NULL)
        return DECLINED;

    /* This method should only be called when the resource is not
     * visible to Apache. We will fetch the resource from the repository,
     * then create a subrequest for Apache to handle.
     */
    err = dav_get_resource(r, 1 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    if (!resource->exists) {
        /* Apache will supply a default error for this. */
        return HTTP_NOT_FOUND;
    }

    /* set up the HTTP headers for the response */
    if ((err = (*resource->hooks->set_headers)(r, resource)) != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             "Unable to set up HTTP headers.",
                             err);
        return dav_handle_err(r, err, NULL);
    }

    if (r->header_only) {
        return DONE;
    }

    /* okay... time to search the content */
    /* Let's validate XML and process walk function
     * in the hook function
     */
    if ((err = (*search_hooks->search_resource)(r, &multi_status)) != NULL) {
        /* ### add a higher-level description? */
        return dav_handle_err(r, err, NULL);
    }

    /* We have results in multi_status */
    /* Should I pass namespace?? */
    dav_send_multistatus(r, HTTP_MULTI_STATUS, multi_status, NULL);

    return DONE;
}