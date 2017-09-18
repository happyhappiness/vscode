        if (tenc) {
            if (!strcasecmp(tenc, "chunked")) {
                ctx->state = BODY_CHUNK;
            }
        }
        else if (lenp) {
            const char *pos = lenp;
            int conversion_error = 0;

            /* This ensures that the number can not be negative. */
            while (apr_isdigit(*pos) || apr_isspace(*pos)) {
                ++pos;
            }

            if (*pos == '\0') {
                char *endstr;

                errno = 0;
                ctx->state = BODY_LENGTH;
                ctx->remaining = strtol(lenp, &endstr, 10);

                if (errno || (endstr && *endstr)) {
                    conversion_error = 1; 
                }
            }

            if (*pos != '\0' || conversion_error) {
                apr_bucket_brigade *bb;

                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                              "Invalid Content-Length");

                bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
