void
parse_externalAclHelper(external_acl ** list)
{
    external_acl *a;
    char *token;
    external_acl_format **p;

    CBDATA_INIT_TYPE_FREECB(external_acl, free_external_acl);
    CBDATA_INIT_TYPE_FREECB(external_acl_format, free_external_acl_format);

    a = cbdataAlloc(external_acl);

    /* set defaults */
    a->ttl = DEFAULT_EXTERNAL_ACL_TTL;
    a->negative_ttl = -1;
    a->children = DEFAULT_EXTERNAL_ACL_CHILDREN;
    a->cache_size = 256*1024;
    a->local_addr.SetLocalhost();
    a->quote = external_acl::QUOTE_METHOD_URL;


    token = strtok(NULL, w_space);

    if (!token)
        self_destruct();

    a->name = xstrdup(token);

    token = strtok(NULL, w_space);

    /* Parse options */
    while (token) {
        if (strncmp(token, "ttl=", 4) == 0) {
            a->ttl = atoi(token + 4);
        } else if (strncmp(token, "negative_ttl=", 13) == 0) {
            a->negative_ttl = atoi(token + 13);
        } else if (strncmp(token, "children=", 9) == 0) {
            a->children = atoi(token + 9);
        } else if (strncmp(token, "concurrency=", 12) == 0) {
            a->concurrency = atoi(token + 12);
        } else if (strncmp(token, "cache=", 6) == 0) {
            a->cache_size = atoi(token + 6);
        } else if (strncmp(token, "grace=", 6) == 0) {
            a->grace = atoi(token + 6);
        } else if (strcmp(token, "protocol=2.5") == 0) {
            a->quote = external_acl::QUOTE_METHOD_SHELL;
        } else if (strcmp(token, "protocol=3.0") == 0) {
            a->quote = external_acl::QUOTE_METHOD_URL;
        } else if (strcmp(token, "quote=url") == 0) {
            a->quote = external_acl::QUOTE_METHOD_URL;
        } else if (strcmp(token, "quote=shell") == 0) {
            a->quote = external_acl::QUOTE_METHOD_SHELL;

            /* INET6: allow admin to configure some helpers explicitly to
                      bind to IPv4/v6 localhost port. */
        } else if (strcmp(token, "ipv4") == 0) {
            if ( !a->local_addr.SetIPv4() ) {
                debugs(3, 0, "WARNING: Error converting " << a->local_addr << " to IPv4 in " << a->name );
            }
        } else if (strcmp(token, "ipv6") == 0) {
            if (!Ip::EnableIpv6)
                debugs(3, 0, "WARNING: --enable-ipv6 required for external ACL helpers to use IPv6: " << a->name );
            // else nothing to do.
        } else {
            break;
        }

        token = strtok(NULL, w_space);
    }

    if (a->negative_ttl == -1)
        a->negative_ttl = a->ttl;

    /* Parse format */
    p = &a->format;

    while (token) {
        external_acl_format *format;

        /* stop on first non-format token found */

        if (*token != '%')
            break;

        format = cbdataAlloc(external_acl_format);

        if (strncmp(token, "%{", 2) == 0) {
            // deprecated. but assume the old configs all referred to request headers.
            debugs(82, DBG_IMPORTANT, "WARNING: external_acl_type format %{...} is being replaced by %>{...} for : " << token);
            parse_header_token(format, (token+2), _external_acl_format::EXT_ACL_HEADER_REQUEST);
        } else if (strncmp(token, "%>{", 3) == 0) {
            parse_header_token(format, (token+3), _external_acl_format::EXT_ACL_HEADER_REQUEST);
        } else if (strncmp(token, "%<{", 3) == 0) {
            parse_header_token(format, (token+3), _external_acl_format::EXT_ACL_HEADER_REPLY);
        } else if (strcmp(token, "%LOGIN") == 0) {
            format->type = _external_acl_format::EXT_ACL_LOGIN;
            a->require_auth = true;
        }

#if USE_IDENT
        else if (strcmp(token, "%IDENT") == 0)
            format->type = _external_acl_format::EXT_ACL_IDENT;

#endif

        else if (strcmp(token, "%SRC") == 0)
            format->type = _external_acl_format::EXT_ACL_SRC;
        else if (strcmp(token, "%SRCPORT") == 0)
            format->type = _external_acl_format::EXT_ACL_SRCPORT;
        else if (strcmp(token, "%MYADDR") == 0)
            format->type = _external_acl_format::EXT_ACL_MYADDR;
        else if (strcmp(token, "%MYPORT") == 0)
            format->type = _external_acl_format::EXT_ACL_MYPORT;
        else if (strcmp(token, "%URI") == 0)
            format->type = _external_acl_format::EXT_ACL_URI;
        else if (strcmp(token, "%DST") == 0)
            format->type = _external_acl_format::EXT_ACL_DST;
        else if (strcmp(token, "%PROTO") == 0)
            format->type = _external_acl_format::EXT_ACL_PROTO;
        else if (strcmp(token, "%PORT") == 0)
            format->type = _external_acl_format::EXT_ACL_PORT;
        else if (strcmp(token, "%PATH") == 0)
            format->type = _external_acl_format::EXT_ACL_PATH;
        else if (strcmp(token, "%METHOD") == 0)
            format->type = _external_acl_format::EXT_ACL_METHOD;

#if USE_SSL

        else if (strcmp(token, "%USER_CERT") == 0)
            format->type = _external_acl_format::EXT_ACL_USER_CERT_RAW;
        else if (strcmp(token, "%USER_CERTCHAIN") == 0)
            format->type = _external_acl_format::EXT_ACL_USER_CERTCHAIN_RAW;
        else if (strncmp(token, "%USER_CERT_", 11) == 0) {
            format->type = _external_acl_format::EXT_ACL_USER_CERT;
            format->header = xstrdup(token + 11);
        } else if (strncmp(token, "%CA_CERT_", 11) == 0) {
            format->type = _external_acl_format::EXT_ACL_USER_CERT;
            format->header = xstrdup(token + 11);
        }

#endif
        else if (strcmp(token, "%EXT_USER") == 0)
            format->type = _external_acl_format::EXT_ACL_EXT_USER;
        else if (strcmp(token, "%%") == 0)
            format->type = _external_acl_format::EXT_ACL_PERCENT;
        else {
            self_destruct();
        }

        *p = format;
        p = &format->next;
        token = strtok(NULL, w_space);
    }

    /* There must be at least one format token */
    if (!a->format)
        self_destruct();

    /* helper */
    if (!token)
        self_destruct();

    wordlistAdd(&a->cmdline, token);

    /* arguments */
    parse_wordlist(&a->cmdline);

    while (*list)
        list = &(*list)->next;

    *list = a;
}