         */
        if (r->content_type == NULL
             || strncmp(r->content_type, "text/html", 9)) {
            const char *env_value = apr_table_get(r->subprocess_env,
                                                  "gzip-only-text/html");
            if ( env_value && (strcmp(env_value,"1") == 0) ) {
                ap_remove_output_filter(f);
                return ap_pass_brigade(f->next, bb);
            }
        }

        /* Let's see what our current Content-Encoding is.
