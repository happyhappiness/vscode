    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }
    /* note: doc == NULL if no request body */

    if (doc && !dav_validate_root(doc, "options")) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00584)
                      "The \"options\" element was not found.");
        return HTTP_BAD_REQUEST;
    }

    /* determine which providers are available */
    dav_level = "1";
