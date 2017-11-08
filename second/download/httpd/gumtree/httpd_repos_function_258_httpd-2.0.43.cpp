void dav_add_all_liveprop_xmlns(apr_pool_t *p, apr_text_header *phdr)
{
    apr_hash_index_t *idx = apr_hash_first(p, dav_liveprop_uris);

    for ( ; idx != NULL; idx = apr_hash_next(idx) ) {
        const void *key;
        void *val;
        const char *s;

        apr_hash_this(idx, &key, NULL, &val);

        s = apr_psprintf(p, " xmlns:lp%d=\"%s\"", (int)val, (const char *)key);
        apr_text_append(p, phdr, s);
    }
}