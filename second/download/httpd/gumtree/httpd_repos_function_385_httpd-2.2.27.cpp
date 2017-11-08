static void dav_insert_xmlns(apr_pool_t *p, const char *pre_prefix, long ns,
                             const char *ns_uri, apr_text_header *phdr)
{
    const char *s;

    s = apr_psprintf(p, " xmlns:%s%ld=\"%s\"", pre_prefix, ns, ns_uri);
    apr_text_append(p, phdr, s);
}