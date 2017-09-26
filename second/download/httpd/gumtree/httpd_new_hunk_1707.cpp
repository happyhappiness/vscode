                     dc && dc->charset_default ? dc->charset_default : "(none)");
    }

    if (!ctx->ran) {  /* filter never ran before */
        chk_filter_chain(f);
        ctx->ran = 1;
        if (!ctx->noop && !ctx->is_sb
            && apr_table_get(f->r->headers_in, "Content-Length")) {
            /* A Content-Length header is present, but it won't be valid after
             * conversion because we're not converting between two single-byte
             * charsets.  This will affect most CGI scripts and may affect
             * some modules.
             * Content-Length can't be unset here because that would break
             * being able to read the request body.
             * Processing of chunked request bodies is not impacted by this
             * filter since the the length was not declared anyway.
             */
            if (dc->debug >= DBGLVL_PMC) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                              "Request body length may change, resulting in "
                              "misprocessing by some modules or scripts");
            }
        }
    }

    if (ctx->noop) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

