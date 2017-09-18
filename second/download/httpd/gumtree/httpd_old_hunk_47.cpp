        ctx.propfind_type = DAV_PROPFIND_IS_PROP;
    }
    else {
        /* "propfind" element must have one of the above three children */

        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                      "The \"propfind\" element does not contain one of "
                      "the required child elements (the specific command).");
        return HTTP_BAD_REQUEST;
    }

    ctx.w.walk_type = DAV_WALKTYPE_NORMAL | DAV_WALKTYPE_AUTH;
