            /* The status out of the front is the same as the status coming in
             * from the back, until further notice.
             */
            r->status = proxy_status;
            r->status_line = proxy_status_line;

            /* read the headers. */
            /* N.B. for HTTP/1.0 clients, we have to fold line-wrapped headers*/
            /* Also, take care with headers with multiple occurences. */

            /* First, tuck away all already existing cookies */
            save_table = apr_table_make(r->pool, 2);
