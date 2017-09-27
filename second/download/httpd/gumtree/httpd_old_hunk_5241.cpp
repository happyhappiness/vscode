
    /* return the underlying error, or OK on success */
    return r->status == HTTP_OK || r->status == OK ? OK : r->status;

}

static void register_hooks(apr_pool_t * p)
{
#if AP_MODULE_MAGIC_AT_LEAST(20080403,1)
    ap_hook_check_authn(authenticate_form_authn, NULL, NULL, APR_HOOK_MIDDLE,
                        AP_AUTH_INTERNAL_PER_CONF);
#else
    ap_hook_check_user_id(authenticate_form_authn, NULL, NULL, APR_HOOK_MIDDLE);
#endif
