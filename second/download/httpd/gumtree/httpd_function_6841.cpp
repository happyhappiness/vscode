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