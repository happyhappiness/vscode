        accf_name = "none";
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                     APLOGNO(02531) "winnt_accept: Listen protocol '%s' has "
                     "no known accept filter. Using 'none' instead",
                     lr->protocol);
    }
    else if (strcmp(accf_name, "data") == 0) {
        accf = 1;
        accf_name = "connect";
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
                     APLOGNO(03458) "winnt_accept: 'data' accept filter is no "
                     "longer supported. Using 'connect' instead");
    }
    else if (strcmp(accf_name, "connect") == 0)
        accf = 1;
    else if (strcmp(accf_name, "none") == 0)
        accf = 0;
    else {
        accf = 0;
