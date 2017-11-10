static int dav_method_get(request_rec *r)
{
    dav_resource *resource;
    dav_error *err;
    int status;

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

    /* Handle conditional requests */
    status = ap_meets_conditions(r);
    if (status) {
      return status;
    }

    if (r->header_only) {
        return DONE;
    }

    /* okay... time to deliver the content */
    if ((err = (*resource->hooks->deliver)(resource,
                                           r->output_filters)) != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             "Unable to deliver content.",
                             err);
        return dav_handle_err(r, err, NULL);
    }

    return DONE;
}