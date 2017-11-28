void
parse_externalAclHelper(external_acl ** list)
{
    char *token = ConfigParser::NextToken();

    if (!token) {
        self_destruct();
        return;
    }

    external_acl *a = new external_acl;
    a->name = xstrdup(token);

    // Allow supported %macros inside quoted tokens
    ConfigParser::EnableMacros();
    token = ConfigParser::NextToken();

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
        } else if (strncmp(token, "queue-size=", 11) == 0) {
            a->children.queue_size = atoi(token + 11);
            a->children.defaultQueueSize = false;
        } else if (strncmp(token, "cache=", 6) == 0) {
            a->cache_size = atoi(token + 6);
        } else if (strncmp(token, "grace=", 6) == 0) {
            a->grace = atoi(token + 6);
        } else if (strcmp(token, "protocol=2.5") == 0) {
            a->quote = Format::LOG_QUOTE_SHELL;
        } else if (strcmp(token, "protocol=3.0") == 0) {
            debugs(3, DBG_PARSE_NOTE(2), "WARNING: external_acl_type option protocol=3.0 is deprecated. Remove this from your config.");
            a->quote = Format::LOG_QUOTE_URL;
        } else if (strcmp(token, "quote=url") == 0) {
            debugs(3, DBG_PARSE_NOTE(2), "WARNING: external_acl_type option quote=url is deprecated. Remove this from your config.");
            a->quote = Format::LOG_QUOTE_URL;
        } else if (strcmp(token, "quote=shell") == 0) {
            debugs(3, DBG_PARSE_NOTE(2), "WARNING: external_acl_type option quote=shell is deprecated. Use protocol=2.5 if still needed.");
            a->quote = Format::LOG_QUOTE_SHELL;

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

        token = ConfigParser::NextToken();
    }
    ConfigParser::DisableMacros();

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

    if (a->children.defaultQueueSize)
        a->children.queue_size = 2 * a->children.n_max;

    /* Legacy external_acl_type format parser.
     * Handles a series of %... tokens where any non-% means
     * the start of another parameter field (ie the path to binary).
     */
    enum Format::Quoting quote = Format::LOG_QUOTE_NONE;
    Format::Token **fmt = &a->format.format;
    bool data_used = false;
    while (token) {
        /* stop on first non-% token found */
        if (*token != '%')
            break;

        *fmt = new Format::Token;
        // these tokens are whitespace delimited
        (*fmt)->space = true;

        // set the default encoding to match the protocol= config
        // this will be overridden by explicit %macro attributes
        (*fmt)->quote = a->quote;

        // compatibility for old tokens incompatible with Format::Token syntax
#if USE_OPENSSL // dont bother if we dont have to.
        if (strncmp(token, "%USER_CERT_", 11) == 0) {
            (*fmt)->type = Format::LFT_EXT_ACL_USER_CERT;
            (*fmt)->data.string = xstrdup(token + 11);
            (*fmt)->data.header.header = (*fmt)->data.string;
        } else if (strncmp(token, "%USER_CA_CERT_", 14) == 0) {
            (*fmt)->type = Format::LFT_EXT_ACL_USER_CA_CERT;
            (*fmt)->data.string = xstrdup(token + 14);
            (*fmt)->data.header.header = (*fmt)->data.string;
        } else if (strncmp(token, "%CA_CERT_", 9) == 0) {
            debugs(82, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: external_acl_type %CA_CERT_* code is obsolete. Use %USER_CA_CERT_* instead");
            (*fmt)->type = Format::LFT_EXT_ACL_USER_CA_CERT;
            (*fmt)->data.string = xstrdup(token + 9);
            (*fmt)->data.header.header = (*fmt)->data.string;
        } else
#endif
        {
            // we can use the Format::Token::parse() method since it
            // only pulls off one token. Since we already checked
            // for '%' prefix above this is guaranteed to be a token.
            const size_t len = (*fmt)->parse(token, &quote);
            assert(len == strlen(token));
        }

        // process special token-specific actions (only if necessary)
#if USE_AUTH
        if ((*fmt)->type == Format::LFT_USER_LOGIN)
            a->require_auth = true;
#endif

        if ((*fmt)->type == Format::LFT_EXT_ACL_DATA)
            data_used = true;

        fmt = &((*fmt)->next);
        token = ConfigParser::NextToken();
    }

    /* There must be at least one format token */
    if (!a->format.format) {
        delete a;
        self_destruct();
        return;
    }

    // format has implicit %DATA on the end if not used explicitly
    if (!data_used) {
        *fmt = new Format::Token;
        (*fmt)->type = Format::LFT_EXT_ACL_DATA;
        (*fmt)->quote = Format::LOG_QUOTE_NONE;
    }

    /* helper */
    if (!token) {
        delete a;
        self_destruct();
        return;
    }

    wordlistAdd(&a->cmdline, token);

    /* arguments */
    parse_wordlist(&a->cmdline);

    while (*list)
        list = &(*list)->next;

    *list = a;
}