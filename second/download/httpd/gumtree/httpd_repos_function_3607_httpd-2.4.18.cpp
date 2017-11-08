static int subnet_parse_arg(ap_expr_lookup_parms *parms)
{
    apr_ipsubnet_t *subnet;
    const char *addr = parms->arg;
    const char *mask;
    apr_status_t ret;

    if (!parms->arg) {
        *parms->err = apr_psprintf(parms->ptemp,
                                   "-%s requires subnet/netmask as constant argument",
                                   parms->name);
        return !OK;
    }

    mask = ap_strchr_c(addr, '/');
    if (mask) {
        addr = apr_pstrmemdup(parms->ptemp, addr, mask - addr);
        mask++;
    }

    ret = apr_ipsubnet_create(&subnet, addr, mask, parms->pool);
    if (ret != APR_SUCCESS) {
        *parms->err = "parsing of subnet/netmask failed";
        return !OK;
    }

    *parms->data = subnet;
    return OK;
}