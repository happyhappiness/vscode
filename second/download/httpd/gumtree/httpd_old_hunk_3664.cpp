        rv = ap_regkey_value_array_get(&svc_args, key, "ConfigArgs", p);
        ap_regkey_close(key);
    }
    if (rv != APR_SUCCESS) {
        if (rv == ERROR_FILE_NOT_FOUND) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL, APLOGNO(00367)
                         "No ConfigArgs registered for %s, perhaps "
                         "this service is not installed?",
                         mpm_service_name);
            return APR_SUCCESS;
        }
        else
            return (rv);
    }
