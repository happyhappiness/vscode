                if (activities->nelts == 0) {
                    /* no href's is a DTD violation:
                       <!ELEMENT activity-set (href+ | new)>
                    */

                    /* This supplies additional info for the default msg. */
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Within the DAV:activity-set element, the "
                                  "DAV:new element must be used, or at least "
                                  "one DAV:href must be specified.");
                    return HTTP_BAD_REQUEST;
                }
            }
