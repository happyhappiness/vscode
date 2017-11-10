static int dav_method_checkout(request_rec *r)
{
    dav_resource *resource;
    dav_resource *working_resource;
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    dav_error *err;
    int result;
    apr_xml_doc *doc;
    int apply_to_vsn = 0;
    int is_unreserved = 0;
    int is_fork_ok = 0;
    int create_activity = 0;
    apr_array_header_t *activities = NULL;

    /* If no versioning provider, decline the request */
    if (vsn_hooks == NULL)
        return DECLINED;

    if ((result = ap_xml_parse_input(r, &doc)) != OK)
        return result;

    if (doc != NULL) {
        const apr_xml_elem *aset;

        if (!dav_validate_root(doc, "checkout")) {
            /* This supplies additional information for the default msg. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00601)
                          "The request body, if present, must be a "
                          "DAV:checkout element.");
            return HTTP_BAD_REQUEST;
        }

        if (dav_find_child(doc->root, "apply-to-version") != NULL) {
            if (apr_table_get(r->headers_in, "label") != NULL) {
                /* ### we want generic 403/409 XML reporting here */
                /* ### DAV:must-not-have-label-and-apply-to-version */
                return dav_error_response(r, HTTP_CONFLICT,
                                          "DAV:apply-to-version cannot be "
                                          "used in conjunction with a "
                                          "Label header.");
            }
            apply_to_vsn = 1;
        }

        is_unreserved = dav_find_child(doc->root, "unreserved") != NULL;
        is_fork_ok = dav_find_child(doc->root, "fork-ok") != NULL;

        if ((aset = dav_find_child(doc->root, "activity-set")) != NULL) {
            if (dav_find_child(aset, "new") != NULL) {
                create_activity = 1;
            }
            else {
                const apr_xml_elem *child = aset->first_child;

                activities = apr_array_make(r->pool, 1, sizeof(const char *));

                for (; child != NULL; child = child->next) {
                    if (child->ns == APR_XML_NS_DAV_ID
                        && strcmp(child->name, "href") == 0) {
                        const char *href;

                        href = dav_xml_get_cdata(child, r->pool,
                                                 1 /* strip_white */);
                        *(const char **)apr_array_push(activities) = href;
                    }
                }

                if (activities->nelts == 0) {
                    /* no href's is a DTD violation:
                       <!ELEMENT activity-set (href+ | new)>
                    */

                    /* This supplies additional info for the default msg. */
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00602)
                                  "Within the DAV:activity-set element, the "
                                  "DAV:new element must be used, or at least "
                                  "one DAV:href must be specified.");
                    return HTTP_BAD_REQUEST;
                }
            }
        }
    }

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, 1 /*label_allowed*/, apply_to_vsn, &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    if (!resource->exists) {
        /* Apache will supply a default error for this. */
        return HTTP_NOT_FOUND;
    }

    /* Check the state of the resource: must be a file or collection,
     * must be versioned, and must not already be checked out.
     */
    if (resource->type != DAV_RESOURCE_TYPE_REGULAR
        && resource->type != DAV_RESOURCE_TYPE_VERSION) {
        return dav_error_response(r, HTTP_CONFLICT,
                                  "Cannot checkout this type of resource.");
    }

    if (!resource->versioned) {
        return dav_error_response(r, HTTP_CONFLICT,
                                  "Cannot checkout unversioned resource.");
    }

    if (r