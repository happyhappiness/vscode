static int hc_expr_lookup(ap_expr_lookup_parms *parms)
{
    switch (parms->type) {
    case AP_EXPR_FUNC_VAR:
        /* for now, we just handle everything that starts with HC_.
         */
        if (strncasecmp(parms->name, "HC_", 3) == 0) {
            *parms->func = hc_expr_var_fn;
            *parms->data = parms->name + 3;
            return OK;
        }
        break;
    case AP_EXPR_FUNC_STRING:
        /* Function HC() is implemented by us.
         */
        if (strcasecmp(parms->name, "HC") == 0) {
            *parms->func = hc_expr_func_fn;
            *parms->data = parms->arg;
            return OK;
        }
        break;
    }
    return DECLINED;
}