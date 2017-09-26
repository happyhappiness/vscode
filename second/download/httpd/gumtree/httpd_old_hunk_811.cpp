     * working.  (IMHO what they really fix is a bug in the users of the code
     * - failing to program correctly for shadow passwords).  We need,
     * therefore, to provide a password. This password can be matched by
     * adding the string "xxj31ZMTZzkVA" as the password in the user file.
     * This is just the crypted variant of the word "password" ;-)
     */
    auth_line = apr_pstrcat(r->pool, "Basic ", 
                            ap_pbase64encode(r->pool, 
                                             apr_pstrcat(r->pool, clientdn, 
                                                         ":password", NULL)),
                            NULL);
    apr_table_set(r->headers_in, "Authorization", auth_line);

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "Faking HTTP Basic Auth header: \"Authorization: %s\"",
