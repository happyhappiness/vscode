        if (tenc) {
            if (!strcasecmp(tenc, "chunked")) {
                ctx->state = BODY_CHUNK;
            }
        }
        else if (lenp) {
            int conversion_error = 0;
            char *endstr;

            ctx->state = BODY_LENGTH;
            errno = 0;
            ctx->remaining = strtol(lenp, &endstr, 10);	/* we depend on ANSI */

            /* This protects us from over/underflow (the errno check),
             * non-digit chars in the string (excluding leading space)
             * (the endstr checks) and a negative number. Depending
             * on the strtol implementation, the errno check may also
             * trigger on an all whitespace string */
            if (errno || (endstr && *endstr) || (ctx->remaining < 0)) {
                 conversion_error = 1; 
            }

            if (conversion_error) {
                apr_bucket_brigade *bb;

                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                              "Invalid Content-Length");

                bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
