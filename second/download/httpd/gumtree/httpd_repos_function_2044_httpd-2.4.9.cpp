static int proxy_match_hostname(struct dirconn_entry *This, request_rec *r)
{
    char *host = This->name;
    const char *host2 = proxy_get_host_of_request(r);
    int h2_len;
    int h1_len;

    if (host == NULL || host2 == NULL) {
        return 0; /* oops! */
    }

    h2_len = strlen(host2);
    h1_len = strlen(host);

#if 0
    struct apr_sockaddr_t *addr = *This->hostaddr;

    /* Try to deal with multiple IP addr's for a host */
    while (addr) {
        if (addr->ipaddr_ptr == ? ? ? ? ? ? ? ? ? ? ? ? ?)
            return 1;
        addr = addr->next;
    }
#endif

    /* Ignore trailing dots in host2 comparison: */
    while (h2_len > 0 && host2[h2_len - 1] == '.') {
        --h2_len;
    }
    while (h1_len > 0 && host[h1_len - 1] == '.') {
        --h1_len;
    }
    return h1_len == h2_len
        && strncasecmp(host, host2, h1_len) == 0;
}