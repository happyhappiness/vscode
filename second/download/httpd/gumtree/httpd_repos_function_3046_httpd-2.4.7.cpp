static void merge_server_configs(apr_pool_t *p, ap_conf_vector_t *base,
                                 ap_conf_vector_t *virt)
{
    /* Can reuse the 'virt' vector for the spine of it, since we don't
     * have to deal with the moral equivalent of .htaccess files here...
     */

    void **base_vector = (void **)base;
    void **virt_vector = (void **)virt;
    module *modp;

    for (modp = ap_top_module; modp; modp = modp->next) {
        merger_func df = modp->merge_server_config;
        int i = modp->module_index;

        if (!virt_vector[i])
            virt_vector[i] = base_vector[i];
        else if (df)
            virt_vector[i] = (*df)(p, base_vector[i], virt_vector[i]);
    }
}