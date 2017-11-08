static void dav_output_prop_name(apr_pool_t *pool,
                                 const dav_prop_name *name,
                                 dav_xmlns_info *xi,
                                 apr_text_header *phdr)
{
    const char *s;

    if (*name->ns == '\0')
        s = apr_psprintf(pool, "<%s/>" DEBUG_CR, name->name);
    else {
        const char *prefix = dav_xmlns_add_uri(xi, name->ns);

        s = apr_psprintf(pool, "<%s:%s/>" DEBUG_CR, prefix, name->name);
    }

    apr_text_append(pool, phdr, s);
}