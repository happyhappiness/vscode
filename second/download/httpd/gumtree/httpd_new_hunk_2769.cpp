            }
            /* test lenp, because it gives another case we can handle */
            else if (!lenp) {
                /* Something that isn't in HTTP, unless some future
                 * edition defines new transfer ecodings, is unsupported.
                 */
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r, APLOGNO(01585)
                              "Unknown Transfer-Encoding: %s", tenc);
                return bail_out_on_error(ctx, f, HTTP_NOT_IMPLEMENTED);
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, f->r, APLOGNO(01586)
                  "Unknown Transfer-Encoding: %s; using Content-Length", tenc);
                tenc = NULL;
            }
        }
        if (lenp && !tenc) {
            char *endstr;
