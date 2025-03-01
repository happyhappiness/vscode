static apr_status_t log_script_err(request_rec *r, apr_file_t *script_err)
{
    char argsbuffer[HUGE_STRING_LEN];
    char *newline;
    apr_status_t rv;
    cgi_server_conf *conf = ap_get_module_config(r->server->module_config, &cgi_module);

    while ((rv = apr_file_gets(argsbuffer, HUGE_STRING_LEN,
                               script_err)) == APR_SUCCESS) {
        newline = strchr(argsbuffer, '\n');
        if (newline) {
            *newline = '\0';
        }
        log_scripterror(r, conf, r->status, 0, APLOGNO(01215), argsbuffer);
    }

    return rv;
}