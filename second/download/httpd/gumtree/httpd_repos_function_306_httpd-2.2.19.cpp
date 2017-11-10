static dav_if_header *dav_add_if_resource(apr_pool_t *p, dav_if_header *next_ih,
                                          const char *uri, apr_size_t uri_len)
{
    dav_if_header *ih;

    if ((ih = apr_pcalloc(p, sizeof(*ih))) == NULL)
        return NULL;

    ih->uri = uri;
    ih->uri_len = uri_len;
    ih->next = next_ih;

    return ih;
}