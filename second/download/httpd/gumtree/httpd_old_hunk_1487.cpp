                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Request header field value presented"
                                  " bad whitespace");
                    return;
                }

                if (tmp_field == last_field) {
                    r->status = HTTP_BAD_REQUEST;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Request header field name was empty");
                    return;
                }
            }
            else /* Using strict RFC7230 parsing */
            {
                /* Ensure valid token chars before ':' per RFC 7230 3.2.4 */
                value = (char *)ap_scan_http_token(last_field);
                if ((value == last_field) || *value != ':') {
