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
