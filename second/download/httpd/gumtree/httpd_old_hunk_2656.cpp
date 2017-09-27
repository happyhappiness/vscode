
            token = ap_get_token(r->pool, &accepts, 0);
            while (token && token[0] && strcasecmp(token, "gzip")) {
                /* skip parameters, XXX: ;q=foo evaluation? */
                while (*accepts == ';') {
                    ++accepts;
                    token = ap_get_token(r->pool, &accepts, 1);
                }

                /* retrieve next token */
                if (*accepts == ',') {
                    ++accepts;
                }
                token = (*accepts) ? ap_get_token(r->pool, &accepts, 0) : NULL;
            }

            /* No acceptable token found. */
            if (token == NULL || token[0] == '\0') {
                ap_remove_output_filter(f);
                return ap_pass_brigade(f->next, bb);
            }
        }

        /* At this point we have decided to filter the content. Let's try to
         * to initialize zlib (except for 304 responses, where we will only
         * send out the headers).
         */

        if (r->status != HTTP_NOT_MODIFIED) {
            ctx = f->ctx = apr_pcalloc(r->pool, sizeof(*ctx));
            ctx->bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
            ctx->buffer = apr_palloc(r->pool, c->bufferSize);
            ctx->libz_end_func = deflateEnd;

            zRC = deflateInit2(&ctx->stream, c->compressionlevel, Z_DEFLATED,
                               c->windowSize, c->memlevel,
                               Z_DEFAULT_STRATEGY);

            if (zRC != Z_OK) {
                deflateEnd(&ctx->stream);
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "unable to init Zlib: "
                              "deflateInit2 returned %d: URL %s",
                              zRC, r->uri);
                /*
                 * Remove ourselves as it does not make sense to return:
                 * We are not able to init libz and pass data down the chain
