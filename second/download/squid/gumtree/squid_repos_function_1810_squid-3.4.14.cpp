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
    a->cache_size = 256*1024;
    a->children.n_max = DEFAULT_EXTERNAL_ACL_CHILDREN;
    a->children.n_startup = a->children.n_max;
    a->children.n_idle = 1;
    a->local_addr.setLocalhost();
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
            a->children.n_max = atoi(token + 9);
            debugs(0, DBG_CRITICAL, "WARNING: external_acl_type option children=N has been deprecated in favor of children-max=N and children-startup=N");
        } else if (strncmp(token, "children-max=", 13) == 0) {
            a->children.n_max = atoi(token + 13);
        } else if (strncmp(token, "children-startup=", 17) == 0) {
            a->children.n_startup = atoi(token + 17);
        } else if (strncmp(token, "children-idle=", 14) == 0) {
            a->children.n_idle = atoi(token + 14);
        } else if (strncmp(token, "concurrency=", 12) == 0) {
            a->children.concurrency = atoi(token + 12);
        } else if (strncmp(token, "cache=", 6) == 0) {
            a->cache_size = atoi(token + 6);
        } else if (strncmp(token, "grace=", 6) == 0) {
            a->grace = atoi(token + 6);
        } else if (strcmp(token, "protocol=2.5") == 0) {
            a->quote = external_acl::QUOTE_METHOD_SHELL;
        } else if (strcmp(token, "protocol=3.0") == 0) {
            debugs(3, DBG_PARSE_NOTE(2), "WARNING: external_acl_type option protocol=3.0 is deprecated. Remove this from your config.");
            a->quote = external_acl::QUOTE_METHOD_URL;
        } else if (strcmp(token, "quote=url") == 0) {
            debugs(3, DBG_PARSE_NOTE(2), "WARNING: external_acl_type option quote=url is deprecated. Remove this from your config.");
            a->quote = external_acl::QUOTE_METHOD_URL;
        } else if (strcmp(token, "quote=shell") == 0) {
            debugs(3, DBG_PARSE_NOTE(2), "WARNING: external_acl_type option quote=shell is deprecated. Use protocol=2.5 if still needed.");
            a->quote = external_acl::QUOTE_METHOD_SHELL;

            /* INET6: allow admin to configure some helpers explicitly to
                      bind to IPv4/v6 localhost port. */
        } else if (strcmp(token, "ipv4") == 0) {
            if ( !a->local_addr.setIPv4() ) {
                debugs(3, DBG_CRITICAL, "WARNING: Error converting " << a->local_addr << " to IPv4 in " << a->name );
            }
        } else if (strcmp(token, "ipv6") == 0) {
            if (!Ip::EnableIpv6)
                debugs(3, DBG_CRITICAL, "WARNING: --enable-ipv6 required for external ACL helpers to use IPv6: " << a->name );
            // else nothing to do.
        } else {
            break;
        }

        token = strtok(NULL, w_space);
    }

    /* check that child startup value is sane. */
    if (a->children.n_startup > a->children.n_max)
        a->children.n_startup = a->children.n_max;

    /* check that child idle value is sane. */
    if (a->children.n_idle > a->children.n_max)
        a->children.n_idle = a->children.n_max;
    if (a->children.n_idle < 1)
        a->children.n_idle = 1;

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
            debugs(82, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: external_acl_type format %{...} is being replaced by %>ha{...} for : " << token);
            parse_header_token(format, (token+2), _external_acl_format::EXT_ACL_HEADER_REQUEST);
        } else if (strncmp(token, "%>{", 3) == 0) {
            debugs(82, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: external_acl_type format %>{...} is being replaced by %>ha{...} for : " << token);
            parse_header_token(format, (token+3), _external_acl_format::EXT_ACL_HEADER_REQUEST);
        } else if (strncmp(token, "%>ha{", 5) == 0) {
            parse_header_token(format, (token+5), _external_acl_format::EXT_ACL_HEADER_REQUEST);
        } else if (strncmp(token, "%<{", 3) == 0) {
            debugs(82, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: external_acl_type format %<{...} is being replaced by %<h{...} for : " << token);
            parse_header_token(format, (token+3), _external_acl_format::EXT_ACL_HEADER_REPLY);
        } else if (strncmp(token, "%<h{", 4) == 0) {
            parse_header_token(format, (token+4), _external_acl_format::EXT_ACL_HEADER_REPLY);
#if USE_AUTH
        } else if (strcmp(token, "%LOGIN") == 0 || strcmp(token, "%ul") == 0) {
            format->type = _external_acl_format::EXT_ACL_LOGIN;
            a->require_auth = true;
#endif
        }
#if USE_IDENT
        else if (strcmp(token, "%IDENT") == 0 || strcmp(token, "%ui") == 0)
            format->type = _external_acl_format::EXT_ACL_IDENT;
#endif
        else if (strcmp(token, "%SRC") == 0 || strcmp(token, "%>a") == 0)
            format->type = _external_acl_format::EXT_ACL_SRC;
        else if (strcmp(token, "%SRCPORT") == 0 || strcmp(token, "%>p") == 0)
            format->type = _external_acl_format::EXT_ACL_SRCPORT;
#if USE_SQUID_EUI
        else if (strcmp(token, "%SRCEUI48") == 0)
            format->type = _external_acl_format::EXT_ACL_SRCEUI48;
        else if (strcmp(token, "%SRCEUI64") == 0)
            format->type = _external_acl_format::EXT_ACL_SRCEUI64;
#endif
        else if (strcmp(token, "%MYADDR") == 0 || strcmp(token, "%la") == 0)
            format->type = _external_acl_format::EXT_ACL_MYADDR;
        else if (strcmp(token, "%MYPORT") == 0 || strcmp(token, "%lp") == 0)
            format->type = _external_acl_format::EXT_ACL_MYPORT;
        else if (strcmp(token, "%URI") == 0 || strcmp(token, "%>ru") == 0)
            format->type = _external_acl_format::EXT_ACL_URI;
        else if (strcmp(token, "%DST") == 0)
            format->type = _external_acl_format::EXT_ACL_DST;
        else if (strcmp(token, "%PROTO") == 0)
            format->type = _external_acl_format::EXT_ACL_PROTO;
        else if (strcmp(token, "%PORT") == 0)
            format->type = _external_acl_format::EXT_ACL_PORT;
        else if (strcmp(token, "%PATH") == 0 || strcmp(token, "%>rp") == 0)
            format->type = _external_acl_format::EXT_ACL_PATH;
        else if (strcmp(token, "%METHOD") == 0 || strcmp(token, "%>rm") == 0)
            format->type = _external_acl_format::EXT_ACL_METHOD;
#if USE_SSL
        else if (strcmp(token, "%USER_CERT") == 0)
            format->type = _external_acl_format::EXT_ACL_USER_CERT_RAW;
        else if (strcmp(token, "%USER_CERTCHAIN") == 0)
            format->type = _external_acl_format::EXT_ACL_USER_CERTCHAIN_RAW;
        else if (strncmp(token, "%USER_CERT_", 11) == 0) {
            format->type = _external_acl_format::EXT_ACL_USER_CERT;
            format->header = xstrdup(token + 11);
        } else if (strncmp(token, "%USER_CA_CERT_", 14) == 0) {
            format->type = _external_acl_format::EXT_ACL_USER_CA_CERT;
            format->header = xstrdup(token + 14);
        } else if (strncmp(token, "%CA_CERT_", 9) == 0) {
            debugs(82, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: external_acl_type %CA_CERT_* code is obsolete. Use %USER_CA_CERT_* instead");
            format->type = _external_acl_format::EXT_ACL_USER_CA_CERT;
            format->header = xstrdup(token + 9);
        }
#endif
#if USE_AUTH
        else if (strcmp(token, "%EXT_USER") == 0)
            format->type = _external_acl_format::EXT_ACL_EXT_USER;
#endif
        else if (strcmp(token, "%EXT_LOG") == 0)
            format->type = _external_acl_format::EXT_ACL_EXT_LOG;
        else if (strcmp(token, "%TAG") == 0)
            format->type = _external_acl_format::EXT_ACL_TAG;
        else if (strcmp(token, "%ACL") == 0)
            format->type = _external_acl_format::EXT_ACL_ACLNAME;
        else if (strcmp(token, "%DATA") == 0)
            format->type = _external_acl_format::EXT_ACL_ACLDATA;
        else if (strcmp(token, "%%") == 0)
            format->type = _external_acl_format::EXT_ACL_PERCENT;
        else {
            debugs(0, DBG_CRITICAL, "ERROR: Unknown Format token " << token);
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