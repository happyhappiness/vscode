static void *merge_dir_conf(apr_pool_t *p, void *basev, void *overridesv)
{
    fcgi_dir_conf *a = (fcgi_dir_conf *)apr_pcalloc(p, sizeof(*a));
    fcgi_dir_conf *base = (fcgi_dir_conf *)basev, 
        *over = (fcgi_dir_conf *)overridesv;

    /* currently we just have a single directive applicable to a 
     * directory, so if it is set then grab all fields from fcgi_dir_conf
     */
    if (over->name) {
        memcpy(a, over, sizeof(*a));
    }
    else {
        memcpy(a, base, sizeof(*a));
    }
    
    return a;
}