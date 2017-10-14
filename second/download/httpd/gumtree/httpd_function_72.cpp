static int dav_method_merge(request_rec *r)
{
    dav_resource *resource;
    dav_resource *source_resource;
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    dav_error *err;
    int result;
    apr_xml_doc *doc;
    apr_xml_elem *source_elem;
    apr_xml_elem *href_elem;
    apr_xml_elem *prop_elem;
    const char *source;
    int no_auto_merge;
    int no_checkout;
    dav_lookup_result lookup;

    /* If no versioning provider, decline the request */
    if (vsn_hooks == NULL)
        return DECLINED;

    if ((result = ap_xml_parse_input(r, &doc)) != OK)
        return result;

    if (doc == NULL || !dav_validate_root(doc, "merge")) {
        /* This supplies additional information for the default msg. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The request body must be present and must be a "
                      "DAV:merge element.");
        return HTTP_BAD_REQUEST;
    }

    if ((source_elem = dav_find_child(doc->root, "source")) == NULL) {
        /* This supplies additional information for the default msg. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The DAV:merge element must contain a DAV:source "
                      "element.");
        return HTTP_BAD_REQUEST;
    }
    if ((href_elem = dav_find_child(source_elem, "href")) == NULL) {
        /* This supplies additional information for the default msg. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The DAV:source element must contain a DAV:href "
                      "element.");
        return HTTP_BAD_REQUEST;
    }
    source = dav_xml_get_cdata(href_elem, r->pool, 1 /* strip_white */);

    /* get a subrequest for the source, so that we can get a dav_resource
       for that source. */
    lookup = dav_lookup_uri(source, r, 0 /* must_be_absolute */);
    if (lookup.rnew == NULL) {
        if (lookup.err.status == HTTP_BAD_REQUEST) {
            /* This supplies additional information for the default message. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          lookup.err.desc);
            return HTTP_BAD_REQUEST;
        }

        /* ### this assumes that dav_lookup_uri() only generates a status
         * ### that Apache can provide a status line for!! */

        return dav_error_response(r, lookup.err.status, lookup.err.desc);
    }
    if (lookup.rnew->status != HTTP_OK) {
        /* ### how best to report this... */
        return dav_error_response(r, lookup.rnew->status,
                                  "Merge source URI had an error.");
    }
    err = dav_get_resource(lookup.rnew, 0 /* label_allowed */,
                           0 /* use_checked_in */, &source_resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    no_auto_merge = dav_find_child(doc->root, "no-auto-merge") != NULL;
    no_checkout = dav_find_child(doc->root, "no-checkout") != NULL;

    prop_elem = dav_find_child(doc->root, "prop");

    /* ### check RFC. I believe the DAV:merge element may contain any
       ### element also allowed within DAV:checkout. need to extract them
       ### here, and pass them along.
       ### if so, then refactor the CHECKOUT method handling so we can reuse
       ### the code. maybe create a structure to hold CHECKOUT parameters
       ### which can be passed to the checkout() and merge() hooks. */

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);
    if (!resource->exists) {
        /* Apache will supply a default error for this. */
        return HTTP_NOT_FOUND;
    }

    /* ### check the source and target resources flags/types */

    /* ### do lock checks, once behavior is defined */

    /* set the Cache-Control header, per the spec */
    /* ### correct? */
    apr_table_setn(r->headers_out, "Cache-Control", "no-cache");

    /* Initialize these values for a standard MERGE response. If the MERGE
       is going to do something different (i.e. an error), then it must
       return a dav_error, and we'll reset these values properly. */
    r->status = HTTP_OK;
    ap_set_content_type(r, "text/xml");

    /* ### should we do any preliminary response generation? probably not,
       ### because we may have an error, thus demanding something else in
       ### the response body. */

    /* Do the merge, including any response generation. */
    if ((err = (*vsn_hooks->merge)(resource, source_resource,
                                   no_auto_merge, no_checkout,
                                   prop_elem,
                                   r->output_filters)) != NULL) {
        /* ### is err->status the right error here? */
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not MERGE resource \"%s\" "
                                          "into \"%s\".",
                                          ap_escape_html(r->pool, source),
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, NULL);
    }

    /* the response was fully generated by the merge() hook. */
    /* ### urk. does this prevent logging? need to check... */
    return DONE;
}