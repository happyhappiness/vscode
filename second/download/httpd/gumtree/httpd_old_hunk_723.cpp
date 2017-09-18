                                   int fixed_args)
{
    apr_array_header_t *svc_args = NULL;
    char conf_key[MAX_PATH];
    char **cmb_data;
    apr_status_t rv;

    apr_snprintf(conf_key, sizeof(conf_key), SERVICEPARAMS, mpm_service_name);
    rv = ap_registry_get_array(p, conf_key, "ConfigArgs", &svc_args);
    if (rv != APR_SUCCESS) {
        if (rv == ERROR_FILE_NOT_FOUND) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL,
                         "No ConfigArgs registered for %s, perhaps "
                         "this service is not installed?", 
                         mpm_service_name);
