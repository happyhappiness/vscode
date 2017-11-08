static int include_expr_lookup(ap_expr_lookup_parms *parms)
{
    switch (parms->type) {
    case AP_EXPR_FUNC_STRING:
        if (strcasecmp(parms->name, "v") == 0 ||
            strcasecmp(parms->name, "reqenv") == 0 ||
            strcasecmp(parms->name, "env") == 0) {
            *parms->func = include_expr_var_fn;
            *parms->data = parms->name;
            return OK;
        }
        break;
    /*
     * We could also make the SSI vars available as %{...} style variables
     * (AP_EXPR_FUNC_VAR), but this would create problems if we ever want
     * to cache parsed expressions for performance reasons.
     */
    }
    return ap_run_expr_lookup(parms);
}