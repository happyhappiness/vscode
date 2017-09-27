     */
    apr_table_addn(r->headers_out, "Cache-Control", "no-store");
    apr_table_addn(r->err_headers_out, "Cache-Control", "no-store");

    /* if set, internal redirect to the logout page */
    if (conf->logout) {
        apr_table_addn(r->headers_out, "Location", conf->logout);
        return HTTP_TEMPORARY_REDIRECT;
    }

    return HTTP_OK;

}

