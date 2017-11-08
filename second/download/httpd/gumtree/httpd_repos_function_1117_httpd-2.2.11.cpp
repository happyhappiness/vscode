static void fully_qualify_uri(request_rec *r)
{
    if (!is_absolute_uri(r->filename)) {
        const char *thisserver;
        char *thisport;
        int port;

        thisserver = ap_get_server_name(r);
        port = ap_get_server_port(r);
        thisport = ap_is_default_port(port, r)
                   ? ""
                   : apr_psprintf(r->pool, ":%u", port);

        r->filename = apr_psprintf(r->pool, "%s://%s%s%s%s",
                                   ap_http_scheme(r), thisserver, thisport,
                                   (*r->filename == '/') ? "" : "/",
                                   r->filename);
    }

    return;
}