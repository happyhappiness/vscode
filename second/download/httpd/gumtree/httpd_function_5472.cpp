char *ap_get_local_host(apr_pool_t *a)
{
#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 256
#endif
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
                (ap_strchr_c(hostname, '.')) ) {
                server_hostname = apr_pstrdup(a, hostname);
                return server_hostname;
            } else if (ap_strchr_c(str, '.')) {
                server_hostname = apr_pstrdup(a, str);
            } else {
                apr_sockaddr_ip_get(&hostname, sockaddr);
                server_hostname = apr_pstrdup(a, hostname);
            }
        } else {
            ap_log_perror(APLOG_MARK, APLOG_STARTUP | APLOG_WARNING, 0, a,
                         "%s: apr_sockaddr_info_get() failed for %s",
                         ap_server_argv0, str);
        }
    }

    if (!server_hostname)
        server_hostname = apr_pstrdup(a, "127.0.0.1");

    ap_log_perror(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0, a,
                 "%s: Could not reliably determine the server's fully qualified "
                 "domain name, using %s for ServerName",
                 ap_server_argv0, server_hostname);

    return server_hostname;
}