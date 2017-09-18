    if (csd && key) {
        int sockdes;
        apr_os_sock_get(&sockdes, csd);


        ret = SSLize_Socket(sockdes, key, r);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Upgradeable socket handle not found");
        return ap_pass_brigade(f->next, bb);
    }
