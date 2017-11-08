static int subreq_ok(request_rec *r)
{
    /*
     * either not in a subrequest, or in a subrequest
     * and URIs aren't NULL and sub/main URIs differ
     */
    return (r->main == NULL
            || (r->main->uri != NULL
                && r->uri != NULL
                && strcmp(r->main->uri, r->uri) != 0));
}