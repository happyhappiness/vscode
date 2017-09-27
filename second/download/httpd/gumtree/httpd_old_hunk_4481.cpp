        accf_name = "none";
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                     APLOGNO(02531) "winnt_accept: Listen protocol '%s' has "
                     "no known accept filter. Using 'none' instead",
                     lr->protocol);
    }
    else if (strcmp(accf_name, "data") == 0)
        accf = 2;
    else if (strcmp(accf_name, "connect") == 0)
        accf = 1;
    else if (strcmp(accf_name, "none") == 0)
        accf = 0;
    else {
        accf = 0;
