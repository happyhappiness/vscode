        return DECLINED;

    if ((result = ap_xml_parse_input(r, &doc)) != OK)
        return result;

    if (doc != NULL) {
        const ap_xml_elem *aset;

        if (!dav_validate_root(doc, "checkout")) {
            /* This supplies additional information for the default msg. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "The request body, if present, must be a "
                          "DAV:checkout element.");
