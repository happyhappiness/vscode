         *  Apply the current rule.
         */
        ctx->vary = NULL;
        rc = apply_rewrite_rule(p, ctx);

        if (rc) {
            /* Regardless of what we do next, we've found a match. Check to see
             * if any of the request header fields were involved, and add them
             * to the Vary field of the response.
             */
            if (ctx->vary) {
                apr_table_merge(r->headers_out, "Vary", ctx->vary);
