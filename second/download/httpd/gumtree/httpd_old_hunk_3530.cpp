                r->err_headers_out = apr_table_overlay(r->pool,
                    r->err_headers_out, cookie_table);
            }
            return cond_status;
        }

        /* if we see a bogus header don't ignore it. Shout and scream */

#if APR_CHARSET_EBCDIC
            /* Chances are that we received an ASCII header text instead of
             * the expected EBCDIC header lines. Try to auto-detect:
             */
