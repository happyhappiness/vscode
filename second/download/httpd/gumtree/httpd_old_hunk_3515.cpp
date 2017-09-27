    char str[MAXHOSTNAMELEN + 1];
    char *server_hostname = NULL;
    apr_sockaddr_t *sockaddr;
    char *hostname;

    if (apr_gethostname(str, sizeof(str) - 1, a) != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_STARTUP | APLOG_WARNING, 0, a,
                     "%s: apr_gethostname() failed to determine ServerName",
                     ap_server_argv0);
    } else {
        str[sizeof(str) - 1] = '\0';
        if (apr_sockaddr_info_get(&sockaddr, str, APR_UNSPEC, 0, 0, a) == APR_SUCCESS) {
            if ( (apr_getnameinfo(&hostname, sockaddr, 0) == APR_SUCCESS) &&
