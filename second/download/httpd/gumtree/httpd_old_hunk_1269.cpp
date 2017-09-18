                              "AuthDigestEnableQueryStringHack")) {
                d_uri.query = r_uri.query;
            }
        }

        if (r->method_number == M_CONNECT) {
            if (strcmp(resp->uri, r_uri.hostinfo)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Digest: uri mismatch - <%s> does not match "
                              "request-uri <%s>", resp->uri, r_uri.hostinfo);
                return HTTP_BAD_REQUEST;
            }
        }
