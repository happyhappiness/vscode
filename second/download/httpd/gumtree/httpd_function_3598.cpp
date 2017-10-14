static int dav_method_options(request_rec *r)
{
    const dav_hooks_locks *locks_hooks = DAV_GET_HOOKS_LOCKS(r);
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    const dav_hooks_binding *binding_hooks = DAV_GET_HOOKS_BINDING(r);
    const dav_hooks_search *search_hooks = DAV_GET_HOOKS_SEARCH(r);
    dav_resource *resource;
    const char *dav_level;
    char *allow;
    char *s;
    const apr_array_header_t *arr;
    const apr_table_entry_t *elts;
    apr_table_t *methods = apr_table_make(r->pool, 12);
    apr_text_header vsn_options = { 0 };
    apr_text_header body = { 0 };
    apr_text *t;
    int text_size;
    int result;
    int i;
    apr_array_header_t *uri_ary;
    apr_xml_doc *doc;
    const apr_xml_elem *elem;
    dav_error *err;

    apr_array_header_t *extensions;
    ap_list_provider_names_t *entry;

    /* resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    /* parse any request body */
    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }
    /* note: doc == NULL if no request body */

    if (doc && !dav_validate_root(doc, "options")) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The \"options\" element was not found.");
        return HTTP_BAD_REQUEST;
    }

    /* determine which providers are available */
    dav_level = "1";

    if (locks_hooks != NULL) {
        dav_level = "1,2";
    }

    if (binding_hooks != NULL)
        dav_level = apr_pstrcat(r->pool, dav_level, ",bindings", NULL);

    /* DAV header additions registered by external modules */
    extensions = ap_list_provider_names(r->pool, DAV_OPTIONS_EXTENSION_GROUP, "0");
    entry = (ap_list_provider_names_t *)extensions->elts;
	
    for (i = 0; i < extensions->nelts; i++, entry++) {
	const dav_options_provider *options = 
	    dav_get_options_providers(entry->provider_name);
	
	if (options && options->dav_header) {
	    apr_text_header hoptions = { 0 };
	    
	    options->dav_header(r, resource, &hoptions);
	    for (t = hoptions.first; t && t->text; t = t->next)
		dav_level = apr_pstrcat(r->pool, dav_level, ",", t->text, NULL);
	}   
    }

    /* ###
     * MSFT Web Folders chokes if length of DAV header value > 63 characters!
     * To workaround that, we use separate DAV headers for versioning and
     * live prop provider namespace URIs.
     * ###
     */
    apr_table_setn(r->headers_out, "DAV", dav_level);

    /*
     * If there is a versioning provider, generate DAV headers
     * for versioning options.
     */
    if (vsn_hooks != NULL) {
        (*vsn_hooks->get_vsn_options)(r->pool, &vsn_options);

        for (t = vsn_options.first; t != NULL; t = t->next)
            apr_table_addn(r->headers_out, "DAV", t->text);
    }

    /*
     * Gather property set URIs from all the liveprop providers,
     * and generate a separate DAV header for each URI, to avoid
     * problems with long header lengths.
     */
    uri_ary = apr_array_make(r->pool, 5, sizeof(const char *));
    dav_run_gather_propsets(uri_ary);
    for (i = 0; i < uri_ary->nelts; ++i) {
        if (((char **)uri_ary->elts)[i] != NULL)
            apr_table_addn(r->headers_out, "DAV", ((char **)uri_ary->elts)[i]);
    }

    /* this tells MSFT products to skip looking for FrontPage extensions */
    apr_table_setn(r->headers_out, "MS-Author-Via", "DAV");

    /*
     * Determine which methods are allowed on the resource.
     * Three cases:  resource is null (3), is lock-null (7.4), or exists.
     *
     * All cases support OPTIONS, and if there is a lock provider, LOCK.
     * (Lock-) null resources also support MKCOL and PUT.
     * Lock-null supports PROPFIND and UNLOCK.
     * Existing resources support lots of stuff.
     */

    apr_table_addn(methods, "OPTIONS", "");

    /* ### take into account resource type */
    switch (dav_get_resource_state(r, resource))
    {
    case DAV_RESOURCE_EXISTS:
        /* resource exists */
        apr_table_addn(methods, "GET", "");
        apr_table_addn(methods, "HEAD", "");
        apr_table_addn(methods, "POST", "");
        apr_table_addn(methods, "DELETE", "");
        apr_table_addn(methods, "TRACE", "");
        apr_table_addn(methods, "PROPFIND", "");
        apr_table_addn(methods, "PROPPATCH", "");
        apr_table_addn(methods, "COPY", "");
        apr_table_addn(methods, "MOVE", "");

        if (!resource->collection)
            apr_table_addn(methods, "PUT", "");

        if (locks_hooks != NULL) {
            apr_table_addn(methods, "LOCK", "");
            apr_table_addn(methods, "UNLOCK", "");
        }

        break;

    case DAV_RESOURCE_LOCK_NULL:
        /* resource is lock-null. */
        apr_table_addn(methods, "MKCOL", "");
        apr_table_addn(methods, "PROPFIND", "");
        apr_table_addn(methods, "PUT", "");

        if (locks_hooks != NULL) {
            apr_table_addn(methods, "LOCK", "");
            apr_table_addn(methods, "UNLOCK", "");
        }

        break;

    case DAV_RESOURCE_NULL:
        /* resource is null. */
        apr_table_addn(methods, "MKCOL", "");
        apr_table_addn(methods, "PUT", "");

        if (locks_hooks != NULL)
            apr_table_addn(methods, "LOCK", "");

        break;

    default:
        /* ### internal error! */
        break;
    }

    /* If there is a versioning provider, add versioning methods */
    if (vsn_hooks != NULL) {
        if (!resource->exists) {
            if ((*vsn_hooks->versionable)(resource))
                apr_table_addn(methods, "VERSION-CONTROL", "");

            if (vsn_hooks->can_be_workspace != NULL
                && (*vsn_hooks->can_be_workspace)(resource))
                apr_table_addn(methods, "MKWORKSPACE", "");

            if (vsn_hooks->can_be_activity != NULL
                && (*vsn_hooks->can_be_activity)(resource))
                apr_table_addn(methods, "MKACTIVITY", "");
        }
        else if (!resource->versioned) {
            if ((*vsn_hooks->versionable)(resource))
                apr_table_addn(methods, "VERSION-CONTROL", "");
        }
        else if (resource->working) {
            apr_table_addn(methods, "CHECKIN", "");

            /* ### we might not support this DeltaV option */
            apr_table_addn(methods, "UNCHECKOUT", "");
        }
        else if (vsn_hooks->add_label != NULL) {
            apr_table_addn(methods, "CHECKOUT", "");
            apr_table_addn(methods, "LABEL", "");
        }
        else {
            apr_table_addn(methods, "CHECKOUT", "");
        }
    }

    /* If there is a bindings provider, see if resource is bindable */
    if (binding_hooks != NULL
        && (*binding_hooks->is_bindable)(resource)) {
        apr_table_addn(methods, "BIND", "");
    }

    /* If there is a search provider, set SEARCH in option */
    if (search_hooks != NULL) {
        apr_table_addn(methods, "SEARCH", "");
    }

    /* additional methods registered by external modules */
    extensions = ap_list_provider_names(r->pool, DAV_OPTIONS_EXTENSION_GROUP, "0");
    entry = (ap_list_provider_names_t *)extensions->elts;
    
    for (i = 0; i < extensions->nelts; i++, entry++) {
	const dav_options_provider *options = 
	    dav_get_options_providers(entry->provider_name);
	
	if (options && options->dav_method) {
	    apr_text_header hoptions = { 0 };
	    
	    options->dav_method(r, resource, &hoptions);
	    for (t = hoptions.first; t && t->text; t = t->next)
		apr_table_addn(methods, t->text, "");
	}    
    }

    /* Generate the Allow header */
    arr = apr_table_elts(methods);
    elts = (const apr_table_entry_t *)arr->elts;
    text_size = 0;

    /* first, compute total length */
    for (i = 0; i < arr->nelts; ++i) {
        if (elts[i].key == NULL)
            continue;

        /* add 1 for comma or null */
        text_size += strlen(elts[i].key) + 1;
    }

    s = allow = apr_palloc(r->pool, text_size);

    for (i = 0; i < arr->nelts; ++i) {
        if (elts[i].key == NULL)
            continue;

        if (s != allow)
            *s++ = ',';

        strcpy(s, elts[i].key);
        s += strlen(s);
    }

    apr_table_setn(r->headers_out, "Allow", allow);


    /* If there is search set_option_head function, set head */
    /* DASL: <DAV:basicsearch>
     * DASL: <http://foo.bar.com/syntax1>
     * DASL: <http://akuma.com/syntax2>
     */
    if (search_hooks != NULL
        && *search_hooks->set_option_head != NULL) {
        if ((err = (*search_hooks->set_option_head)(r)) != NULL) {
            return dav_handle_err(r, err, NULL);
        }
    }

    /* if there was no request body, then there is no response body */
    if (doc == NULL) {
        ap_set_content_length(r, 0);

        /* ### this sends a Content-Type. the default OPTIONS does not. */

        /* ### the default (ap_send_http_options) returns OK, but I believe
         * ### that is because it is the default handler and nothing else
         * ### will run after the thing. */
        return DONE;
    }

    /* handle each options request */
    for (elem = doc->root->first_child; elem != NULL; elem = elem->next) {
        /* check for something we recognize first */
        int core_option = 0;
        dav_error *err = NULL;

        if (elem->ns == APR_XML_NS_DAV_ID) {
            if (strcmp(elem->name, "supported-method-set") == 0) {
                err = dav_gen_supported_methods(r, elem, methods, &body);
                core_option = 1;
            }
            else if (strcmp(elem->name, "supported-live-property-set") == 0) {
                err = dav_gen_supported_live_props(r, resource, elem, &body);
                core_option = 1;
            }
            else if (strcmp(elem->name, "supported-report-set") == 0) {
                err = dav_gen_supported_reports(r, resource, elem, vsn_hooks, &body);
                core_option = 1;
            }
        }

        if (err != NULL)
            return dav_handle_err(r, err, NULL);

        /* if unrecognized option, pass to versioning provider */
        if (!core_option && vsn_hooks != NULL) {
            if ((err = (*vsn_hooks->get_option)(resource, elem, &body))
                != NULL) {
                return dav_handle_err(r, err, NULL);
            }
        }
    }

    /* send the options response */
    r->status = HTTP_OK;
    ap_set_content_type(r, DAV_XML_CONTENT_TYPE);

    /* send the headers and response body */
    ap_rputs(DAV_XML_HEADER DEBUG_CR
             "<D:options-response xmlns:D=\"DAV:\">" DEBUG_CR, r);

    for (t = body.first; t != NULL; t = t->next)
        ap_rputs(t->text, r);

    ap_rputs("</D:options-response>" DEBUG_CR, r);

    /* we've sent everything necessary to the client. */
    return DONE;
}