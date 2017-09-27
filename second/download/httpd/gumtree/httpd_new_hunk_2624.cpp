    if ((result = ap_xml_parse_input(r, &doc)) != OK)
        return result;

    if (doc != NULL) {
        if (!dav_validate_root(doc, "checkin")) {
            /* This supplies additional information for the default msg. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00603)
                          "The request body, if present, must be a "
                          "DAV:checkin element.");
            return HTTP_BAD_REQUEST;
        }

        keep_checked_out = dav_find_child(doc->root, "keep-checked-out") != NULL;
