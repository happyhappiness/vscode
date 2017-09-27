        /*
         * If the script returned a specific status, that's what
         * we'll use - otherwise we assume 200 OK.
         */
        else if (!strcasecmp(w, "Status")) {
            r->status = cgi_status = atoi(l);
            r->status_line = apr_pstrdup(r->pool, l);
        }
        else if (!strcasecmp(w, "Location")) {
            apr_table_set(r->headers_out, w, l);
        }
        else if (!strcasecmp(w, "Content-Length")) {
