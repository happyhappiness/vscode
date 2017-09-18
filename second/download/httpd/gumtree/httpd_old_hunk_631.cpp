                          "The \"version\" element does not contain "
                          "an \"href\" element.");
            return HTTP_BAD_REQUEST;
        }

        /* get version URI */
        ap_xml_to_text(r->pool, child, AP_XML_X2T_INNER, NULL, NULL,
                       &target, &tsize);
        if (tsize == 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "An \"href\" element does not contain a URI.");
            return HTTP_BAD_REQUEST;
        }
    }
