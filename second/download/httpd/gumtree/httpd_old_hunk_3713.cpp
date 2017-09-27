                 * Section 3.3.3.3: "If a Transfer-Encoding header field is
                 * present in a response and the chunked transfer coding is not
                 * the final encoding, the message body length is determined by
                 * reading the connection until it is closed by the server."
                 */
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r, APLOGNO(02555)
                              "Unknown Transfer-Encoding: %s;"
                              " using read-until-close", tenc);
                tenc = NULL;
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r, APLOGNO(01585)
                              "Unknown Transfer-Encoding: %s", tenc);
                return bail_out_on_error(ctx, f, HTTP_NOT_IMPLEMENTED);
            }
            lenp = NULL;
        }
        if (lenp) {
            char *endstr;

