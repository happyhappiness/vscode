
    /* return the underlying error, or OK on success */
    return r->status == HTTP_OK || r->status == OK ? OK : r->status;

}

static int authenticate_form_post_config(apr_pool_t *pconf, apr_pool_t *plog,
        apr_pool_t *ptemp, server_rec *s)
{

    if (!ap_session_load_fn || !ap_session_get_fn || !ap_session_set_fn) {
        ap_session_load_fn = APR_RETRIEVE_OPTIONAL_FN(ap_session_load);
        ap_session_get_fn = APR_RETRIEVE_OPTIONAL_FN(ap_session_get);
        ap_session_set_fn = APR_RETRIEVE_OPTIONAL_FN(ap_session_set);
        if (!ap_session_load_fn || !ap_session_get_fn || !ap_session_set_fn) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL, APLOGNO(02617)
                    "You must load mod_session to enable the mod_auth_form "
                                       "functions");
            return !OK;
        }
    }

    if (!ap_request_insert_filter_fn || !ap_request_remove_filter_fn) {
        ap_request_insert_filter_fn = APR_RETRIEVE_OPTIONAL_FN(ap_request_insert_filter);
        ap_request_remove_filter_fn = APR_RETRIEVE_OPTIONAL_FN(ap_request_remove_filter);
        if (!ap_request_insert_filter_fn || !ap_request_remove_filter_fn) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL, APLOGNO(02618)
                    "You must load mod_request to enable the mod_auth_form "
                                       "functions");
            return !OK;
        }
    }

    return OK;
}

static void register_hooks(apr_pool_t * p)
{
    ap_hook_post_config(authenticate_form_post_config,NULL,NULL,APR_HOOK_MIDDLE);

#if AP_MODULE_MAGIC_AT_LEAST(20080403,1)
    ap_hook_check_authn(authenticate_form_authn, NULL, NULL, APR_HOOK_MIDDLE,
                        AP_AUTH_INTERNAL_PER_CONF);
#else
    ap_hook_check_user_id(authenticate_form_authn, NULL, NULL, APR_HOOK_MIDDLE);
#endif
