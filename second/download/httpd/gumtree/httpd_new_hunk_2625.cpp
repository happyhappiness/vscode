    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }

    if (doc == NULL || !dav_validate_root(doc, "update")) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00604)
                      "The request body does not contain "
                      "an \"update\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* check for label-name or version element, but not both */
    if ((child = dav_find_child(doc->root, "label-name")) != NULL)
        is_label = 1;
    else if ((child = dav_find_child(doc->root, "version")) != NULL) {
        /* get the href element */
        if ((child = dav_find_child(child, "href")) == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00605)
                          "The version element does not contain "
                          "an \"href\" element.");
            return HTTP_BAD_REQUEST;
        }
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00606)
                      "The \"update\" element does not contain "
                      "a \"label-name\" or \"version\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* a depth greater than zero is only allowed for a label */
    if (!is_label && depth != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00607)
                      "Depth must be zero for UPDATE with a version");
        return HTTP_BAD_REQUEST;
    }

    /* get the target value (a label or a version URI) */
    apr_xml_to_text(r->pool, child, APR_XML_X2T_INNER, NULL, NULL,
                    &target, &tsize);
    if (tsize == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00608)
                      "A \"label-name\" or \"href\" element does not contain "
                      "any content.");
        return HTTP_BAD_REQUEST;
    }

    /* Ask repository module to resolve the resource */
