        }
    }

    if (!server_hostname) 
        server_hostname = apr_pstrdup(a, "127.0.0.1");

    ap_log_perror(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO|APLOG_STARTUP, 0, a,
                 "%s: Could not determine the server's fully qualified "
                 "domain name, using %s for ServerName",
                 ap_server_argv0, server_hostname);
             
    return server_hostname;
}
