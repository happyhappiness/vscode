    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }
    /* note: doc == NULL if no request body */

    if (doc != NULL) {
        const ap_xml_elem *child;
        apr_size_t tsize;

        if (!dav_validate_root(doc, "version-control")) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "The request body does not contain "
                          "a \"version-control\" element.");
