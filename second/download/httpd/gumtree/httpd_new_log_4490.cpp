ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00900)
                         "Warning: NetMask not supplied with IP-Addr; guessing: %s/%ld",
                         inet_ntoa(This->addr), bits);