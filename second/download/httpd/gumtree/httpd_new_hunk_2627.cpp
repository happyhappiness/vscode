    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }

    if (doc == NULL || !dav_validate_root(doc, "label")) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00610)
                      "The request body does not contain "
                      "a \"label\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* check for add, set, or remove element */
