
    if (doc != NULL) {
        const apr_xml_elem *child;
        apr_size_t tsize;

        if (!dav_validate_root(doc, "version-control")) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00597)
                          "The request body does not contain "
                          "a \"version-control\" element.");
            return HTTP_BAD_REQUEST;
        }

        /* get the version URI */
        if ((child = dav_find_child(doc->root, "version")) == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00598)
                          "The \"version-control\" element does not contain "
                          "a \"version\" element.");
            return HTTP_BAD_REQUEST;
        }

        if ((child = dav_find_child(child, "href")) == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00599)
                          "The \"version\" element does not contain "
                          "an \"href\" element.");
            return HTTP_BAD_REQUEST;
        }

        /* get version URI */
        apr_xml_to_text(r->pool, child, APR_XML_X2T_INNER, NULL, NULL,
                        &target, &tsize);
        if (tsize == 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00600)
                          "An \"href\" element does not contain a URI.");
            return HTTP_BAD_REQUEST;
        }
    }

    /* Check request preconditions */
