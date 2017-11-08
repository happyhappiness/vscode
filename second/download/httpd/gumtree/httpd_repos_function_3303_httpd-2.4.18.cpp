static int expr_lookup_fn(ap_expr_lookup_parms *parms)
{
    if (parms->type == AP_EXPR_FUNC_VAR
        && strcasecmp(parms->name, "REMOTE_USER") == 0) {
        struct require_expr_info *info;
        apr_pool_userdata_get((void**)&info, REQUIRE_EXPR_NOTE, parms->ptemp);
        AP_DEBUG_ASSERT(info != NULL);
        info->want_user = 1;
    }
    return ap_expr_lookup_default(parms);
}