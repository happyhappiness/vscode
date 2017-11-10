static void setupenv(request_rec *r, const char *password, const char *apache_role)
{
    ap_add_common_vars(r);
    ap_add_cgi_vars(r);
    apr_table_setn(r->subprocess_env, "FCGI_ROLE", AP_FCGI_AUTHORIZER_STR);
    if (apache_role) {
        apr_table_setn(r->subprocess_env, "FCGI_APACHE_ROLE", apache_role);
    }
    if (password) {
        apr_table_setn(r->subprocess_env, "REMOTE_PASSWD", password);
    }
    /* Drop the variables CONTENT_LENGTH, PATH_INFO, PATH_TRANSLATED,
     * SCRIPT_NAME and most Hop-By-Hop headers - EXCEPT we will pass
     * PROXY_AUTH to allow CGI to perform proxy auth for httpd
     */
    apr_table_unset(r->subprocess_env, "CONTENT_LENGTH");
    apr_table_unset(r->subprocess_env, "PATH_INFO");
    apr_table_unset(r->subprocess_env, "PATH_TRANSLATED");
    apr_table_unset(r->subprocess_env, "SCRIPT_NAME");
    apr_table_unset(r->subprocess_env, "HTTP_KEEP_ALIVE");
    apr_table_unset(r->subprocess_env, "HTTP_TE");
    apr_table_unset(r->subprocess_env, "HTTP_TRAILER");
    apr_table_unset(r->subprocess_env, "HTTP_TRANSFER_ENCODING");
    apr_table_unset(r->subprocess_env, "HTTP_UPGRADE");

    /* Connection hop-by-hop header to prevent the CGI from hanging */
    apr_table_setn(r->subprocess_env, "HTTP_CONNECTION", "close");
}