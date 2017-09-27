        ctx.label_op = DAV_LABEL_SET;
    }
    else if ((child = dav_find_child(doc->root, "remove")) != NULL) {
        ctx.label_op = DAV_LABEL_REMOVE;
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The \"label\" element does not contain "
                      "an \"add\", \"set\", or \"remove\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* get the label string */
    if ((child = dav_find_child(child, "label-name")) == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The label command element does not contain "
                      "a \"label-name\" element.");
        return HTTP_BAD_REQUEST;
    }

    apr_xml_to_text(r->pool, child, APR_XML_X2T_INNER, NULL, NULL,
                    &ctx.label, &tsize);
    if (tsize == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "A \"label-name\" element does not contain "
                      "a label name.");
        return HTTP_BAD_REQUEST;
    }

    /* do the label operation walk */
