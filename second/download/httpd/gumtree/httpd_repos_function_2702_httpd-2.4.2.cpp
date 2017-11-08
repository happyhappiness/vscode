static const char *ip_parse_config(cmd_parms *cmd,
                                   const char *require_line,
                                   const void **parsed_require_line)
{
    const char *t, *w;
    int count = 0;
    apr_ipsubnet_t **ip;
    apr_pool_t *ptemp = cmd->temp_pool;
    apr_pool_t *p = cmd->pool;

    /* The 'ip' provider will allow the configuration to specify a list of
        ip addresses to check rather than a single address.  This is different
        from the previous host based syntax. */

    t = require_line;
    while ((w = ap_getword_conf(ptemp, &t)) && w[0])
        count++;

    if (count == 0)
        return "'require ip' requires an argument";

    ip = apr_pcalloc(p, sizeof(apr_ipsubnet_t *) * (count + 1));
    *parsed_require_line = ip;

    t = require_line;
    while ((w = ap_getword_conf(ptemp, &t)) && w[0]) {
        char *addr = apr_pstrdup(ptemp, w);
        char *mask;
        apr_status_t rv;

        if (parsed_subnets &&
            (*ip = apr_hash_get(parsed_subnets, w, APR_HASH_KEY_STRING)) != NULL)
        {
            /* we already have parsed this subnet */
            ip++;
            continue;
        }

        if ((mask = ap_strchr(addr, '/')))
            *mask++ = '\0';

        rv = apr_ipsubnet_create(ip, addr, mask, p);

        if(APR_STATUS_IS_EINVAL(rv)) {
            /* looked nothing like an IP address */
            return apr_psprintf(p, "ip address '%s' appears to be invalid", w);
        }
        else if (rv != APR_SUCCESS) {
            char msgbuf[120];
            apr_strerror(rv, msgbuf, sizeof msgbuf);
            return apr_psprintf(p, "ip address '%s' appears to be invalid: %s",
                                w, msgbuf);
        }

        if (parsed_subnets)
            apr_hash_set(parsed_subnets, w, APR_HASH_KEY_STRING, *ip);
        ip++;
    }

    return NULL;
}