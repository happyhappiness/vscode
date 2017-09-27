        return result;
    }
    /* note: doc == NULL if no request body */

    if (doc == NULL || !dav_validate_root(doc, "propertyupdate")) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00587)
                      "The request body does not contain "
                      "a \"propertyupdate\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* Check If-Headers and existing locks */
