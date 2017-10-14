char *ap_get_local_host(apr_pool_t *a)
{
#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 256
#endif
    char str[MAXHOSTNAMELEN + 1];
    char *server_hostname = NULL;
    struct hostent *p;

#ifdef BEOS_R5
    if (gethostname(str, sizeof(str) - 1) == 0)
#else
    if (gethostname(str, sizeof(str) - 1) != 0)
#endif
    {
        ap_log_perror(APLOG_MARK, APLOG_STARTUP | APLOG_WARNING, 0, a,
                     "%s: gethostname() failed to determine ServerName",
                     ap_server_argv0);
    }
    else 
    {
        str[sizeof(str) - 1] = '\0';
        /* TODO: Screaming for APR-ization */
        if ((!(p = gethostbyname(str))) 
            || (!(server_hostname = find_fqdn(a, p)))) {
            /* Recovery - return the default servername by IP: */
            if (p && p->h_addr_list[0]) {
                apr_snprintf(str, sizeof(str), "%pA", p->h_addr_list[0]);
                server_hostname = apr_pstrdup(a, str);
                /* We will drop through to report the IP-named server */
            }
        }
        else {
            /* Since we found a fdqn, return it with no logged message. */
            return server_hostname;
        }
    }

    if (!server_hostname) 
        server_hostname = apr_pstrdup(a, "127.0.0.1");

    ap_log_perror(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0, a,
                 "%s: Could not determine the server's fully qualified "
                 "domain name, using %s for ServerName",
                 ap_server_argv0, server_hostname);
             
    return server_hostname;
}