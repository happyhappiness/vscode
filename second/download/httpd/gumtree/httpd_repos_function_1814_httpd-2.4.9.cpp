static void register_one_method(apr_pool_t *p, const char *methname,
                                int methnum)
{
    int *pnum = apr_palloc(p, sizeof(*pnum));

    *pnum = methnum;
    apr_hash_set(methods_registry, methname, APR_HASH_KEY_STRING, pnum);
}