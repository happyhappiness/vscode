static void remove_items(apr_pool_t *p, apr_array_header_t *remove,
                         apr_hash_t *mappings)
{
    attrib_info *suffix = (attrib_info *) remove->elts;
    int i;
    for (i = 0; i < remove->nelts; i++) {
        extension_info *exinfo = apr_hash_get(mappings,
                                              suffix[i].name,
                                              APR_HASH_KEY_STRING);
        if (exinfo && *(const char**)((char *)exinfo + suffix[i].offset)) {
            extension_info *copyinfo = exinfo;
            exinfo = (extension_info*)apr_palloc(p, sizeof(*exinfo));
            apr_hash_set(mappings, suffix[i].name,
                         APR_HASH_KEY_STRING, exinfo);
            memcpy(exinfo, copyinfo, sizeof(*exinfo));
            *(const char**)((char *)exinfo + suffix[i].offset) = NULL;
        }
    }
}