static void fully_qualify_uri(request_rec *r)
{
    char buf[32];
    const char *thisserver;
    char *thisport;
    int port;

    if (!is_absolute_uri(r->filename)) {

        thisserver = ap_get_server_name(r);
        port = ap_get_server_port(r);
        if (ap_is_default_port(port,r)) {
            thisport = "";
        }
        else {
            apr_snprintf(buf, sizeof(buf), ":%u", port);
            thisport = buf;
        }

        if (r->filename[0] == '/') {
            r->filename = apr_psprintf(r->pool, "%s://%s%s%s",
                                      ap_http_method(r), thisserver,
                                      thisport, r->filename);
        }
        else {
            r->filename = apr_psprintf(r->pool, "%s://%s%s/%s",
                                      ap_http_method(r), thisserver,
                                      thisport, r->filename);
        }
    }
    return;
}