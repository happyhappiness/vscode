ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL,
                         "No ConfigArgs registered for %s, perhaps "
                         "this service is not installed?",
                         mpm_service_name);