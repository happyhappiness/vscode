static int dav_method_make_activity(request_rec *r)
{
    dav_resource *resource;
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    dav_error *err;
    int result;

    /* if no versioning provider, or the provider does not support activities,
     * decline the request
     */
    if (vsn_hooks == NULL || vsn_hooks->make_activity == NULL)
        return DECLINED;

    /* ask repository module to resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    /* MKACTIVITY does not have a defined request body. */
    if ((result = ap_discard_request_body(r)) != OK) {
        return result;
    }

    /* Check request preconditions */

    /* ### need a general mechanism for reporting precondition violations
     * ### (should be returning XML document for 403/409 responses)
     */

    /* resource must not already exist */
    if (resource->exists) {
        err = dav_new_error(r->pool, HTTP_CONFLICT, 0,
                            "<DAV:resource-must-be-null/>");
        return dav_handle_err(r, err, NULL);
    }

    /* the provider must say whether the resource can be created as
       an activity, i.e. whether the location is ok.  */
    if (vsn_hooks->can_be_activity != NULL
        && !(*vsn_hooks->can_be_activity)(resource)) {
      err = dav_new_error(r->pool, HTTP_FORBIDDEN, 0,
                          "<DAV:activity-location-ok/>");
      return dav_handle_err(r, err, NULL);
    }

    /* ### what about locking? */

    /* attempt to create the activity */
    if ((err = (*vsn_hooks->make_activity)(resource)) != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not create activity %s.",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, NULL);
    }

    /* set the Cache-Control header, per the spec */
    apr_table_setn(r->headers_out, "Cache-Control", "no-cache");

    /* return an appropriate response (HTTP_CREATED) */
    return dav_created(r, resource->uri, "Activity", 0 /*replaced*/);
}