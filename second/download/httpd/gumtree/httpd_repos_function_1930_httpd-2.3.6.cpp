static void *merge_reflector_dir_config(apr_pool_t * p, void *basev, void *addv)
{
    reflector_cfg *new = (reflector_cfg *) apr_pcalloc(p,
            sizeof(reflector_cfg));
    reflector_cfg *add = (reflector_cfg *) addv;
    reflector_cfg *base = (reflector_cfg *) basev;

    new->headers = apr_table_overlay(p, add->headers, base->headers);

    return new;
}