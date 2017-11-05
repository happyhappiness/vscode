static int dav_init_handler(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp,
                             server_rec *s)
{
    /* DBG0("dav_init_handler"); */

    /* Register DAV methods */
    dav_methods[DAV_M_BIND] = ap_method_register(p, "BIND");
    dav_methods[DAV_M_SEARCH] = ap_method_register(p, "SEARCH");

    ap_add_version_component(p, "DAV/2");

    return OK;
}