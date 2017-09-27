ap_log_perror(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0, a, APLOGNO(00558)
                 "%s: Could not reliably determine the server's fully qualified "
                 "domain name, using %s. Set the 'ServerName' directive globally "
                 "to suppress this message",
                 ap_server_argv0, server_hostname);