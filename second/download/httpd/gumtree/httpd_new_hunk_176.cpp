             * HTTP/1.0 specification).
             */
            return HTTP_MULTIPLE_CHOICES;
        }
        
        if (!*bestp) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "no acceptable variant: %s", r->filename);
            return HTTP_NOT_ACCEPTABLE;
        }
    }

    /* Variant selection chose a variant */
