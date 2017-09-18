        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Depth must be zero for UPDATE with a version");
        return HTTP_BAD_REQUEST;
    }

    /* get the target value (a label or a version URI) */
    ap_xml_to_text(r->pool, child, AP_XML_X2T_INNER, NULL, NULL,
                   &target, &tsize);
    if (tsize == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "A \"label-name\" or \"href\" element does not contain "
                      "any content.");
        return HTTP_BAD_REQUEST;
    }
