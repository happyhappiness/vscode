static int dav_method_make_workspace(request_rec *r)
{
    dav_resource *resource;
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    dav_error *err;
    apr_xml_doc *doc;
    int result;

    /* if no versioning provider, or the provider does not support workspaces,
     * decline the request
     */
    if (vsn_hooks == NULL || vsn_hooks->make_workspace == NULL)
        return DECLINED;

    /* ask repository module to resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    /* parse the request body (must be a mkworkspace element) */
    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }

    if (doc == NULL
        || !dav_validate_root(doc, "mkworkspace")) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The request body does not contain "
                      "a \"mkworkspace\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* Check request preconditions */

    /* ### need a general mechanism for reporting precondition violations
     * ### (should be returning XML document for 403/409 responses)
     */

    /* resource must not already exist */
    if (resource->exists) {
        err = dav_new_error(r->pool, HTTP_CONFLICT, 0, 0,
                            "<DAV:resource-must-be-null/>");
        return dav_handle_err(r, err, NULL);
    }

    /* ### what about locking? */

    /* attempt to create the workspace */
    if ((err = (*vsn_hooks->make_workspace)(resource, doc)) != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not create workspace %s.",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, NULL);
    }

    /* set the Cache-Control header, per the spec */
    apr_table_setn(r->headers_out, "Cache-Control", "no-cache");

    /* return an appropriate response (HTTP_CREATED) */
    return dav_created(r, resource->uri, "Workspace", 0 /*replaced*/);
}