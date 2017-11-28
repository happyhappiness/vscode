void
dump_externalAclHelper(StoreEntry * sentry, const char *name, const external_acl * list)
{
    const external_acl *node;
    const wordlist *word;

    for (node = list; node; node = node->next) {
        storeAppendPrintf(sentry, "%s %s", name, node->name);

        if (!node->local_addr.isIPv6())
            storeAppendPrintf(sentry, " ipv4");
        else
            storeAppendPrintf(sentry, " ipv6");

        if (node->ttl != DEFAULT_EXTERNAL_ACL_TTL)
            storeAppendPrintf(sentry, " ttl=%d", node->ttl);

        if (node->negative_ttl != node->ttl)
            storeAppendPrintf(sentry, " negative_ttl=%d", node->negative_ttl);

        if (node->grace)
            storeAppendPrintf(sentry, " grace=%d", node->grace);

        if (node->children.n_max != DEFAULT_EXTERNAL_ACL_CHILDREN)
            storeAppendPrintf(sentry, " children-max=%d", node->children.n_max);

        if (node->children.n_startup != 0) // sync with helper/ChildConfig.cc default
            storeAppendPrintf(sentry, " children-startup=%d", node->children.n_startup);

        if (node->children.n_idle != 1) // sync with helper/ChildConfig.cc default
            storeAppendPrintf(sentry, " children-idle=%d", node->children.n_idle);

        if (node->children.concurrency != 0)
            storeAppendPrintf(sentry, " concurrency=%d", node->children.concurrency);

        if (node->cache)
            storeAppendPrintf(sentry, " cache=%d", node->cache_size);

        if (node->quote == external_acl::QUOTE_METHOD_SHELL)
            storeAppendPrintf(sentry, " protocol=2.5");

        for (external_acl_format::Pointer format = node->format; format!= NULL; format = format->next) {
            switch (format->type) {

            case Format::LFT_ADAPTED_REQUEST_HEADER:
                storeAppendPrintf(sentry, " %%>ha{%s}", format->header);
                break;

            case Format::LFT_ADAPTED_REQUEST_HEADER_ELEM:
                storeAppendPrintf(sentry, " %%>ha{%s:%s}", format->header, format->member);
                break;

            case Format::LFT_REPLY_HEADER:
                storeAppendPrintf(sentry, " %%<h{%s}", format->header);
                break;

            case Format::LFT_REPLY_HEADER_ELEM:
                storeAppendPrintf(sentry, " %%<h{%s:%s}", format->header, format->member);
                break;

#define DUMP_EXT_ACL_TYPE_FMT(a, fmt, ...) \
            case Format::LFT_##a: \
                storeAppendPrintf(sentry, fmt, ##__VA_ARGS__); \
                break
#if USE_AUTH
                DUMP_EXT_ACL_TYPE_FMT(USER_LOGIN," %%ul");
                DUMP_EXT_ACL_TYPE_FMT(USER_NAME," %%un");
#endif
#if USE_IDENT

                DUMP_EXT_ACL_TYPE_FMT(USER_IDENT," %%ui");
#endif
                DUMP_EXT_ACL_TYPE_FMT(CLIENT_IP_ADDRESS," %%>a");
                DUMP_EXT_ACL_TYPE_FMT(CLIENT_PORT," %%>p");
#if USE_SQUID_EUI
                DUMP_EXT_ACL_TYPE_FMT(EXT_ACL_CLIENT_EUI48," %%SRCEUI48");
                DUMP_EXT_ACL_TYPE_FMT(EXT_ACL_CLIENT_EUI64," %%SRCEUI64");
#endif
                DUMP_EXT_ACL_TYPE_FMT(LOCAL_LISTENING_IP," %%>la");
                DUMP_EXT_ACL_TYPE_FMT(LOCAL_LISTENING_PORT," %%>lp");
                DUMP_EXT_ACL_TYPE_FMT(CLIENT_REQ_URI," %%>ru");
                DUMP_EXT_ACL_TYPE_FMT(CLIENT_REQ_URLDOMAIN," %%>rd");
                DUMP_EXT_ACL_TYPE_FMT(CLIENT_REQ_URLSCHEME," %%>rs");
                DUMP_EXT_ACL_TYPE_FMT(CLIENT_REQ_URLPORT," %%>rP");
                DUMP_EXT_ACL_TYPE_FMT(CLIENT_REQ_URLPATH," %%>rp");
                DUMP_EXT_ACL_TYPE_FMT(CLIENT_REQ_METHOD," %%>rm");
#if USE_OPENSSL
                DUMP_EXT_ACL_TYPE_FMT(EXT_ACL_USER_CERT_RAW, " %%USER_CERT_RAW");
                DUMP_EXT_ACL_TYPE_FMT(EXT_ACL_USER_CERTCHAIN_RAW, " %%USER_CERTCHAIN_RAW");
                DUMP_EXT_ACL_TYPE_FMT(EXT_ACL_USER_CERT, " %%USER_CERT_%s", format->header);
                DUMP_EXT_ACL_TYPE_FMT(EXT_ACL_USER_CA_CERT, " %%USER_CA_CERT_%s", format->header);
                DUMP_EXT_ACL_TYPE_FMT(SSL_CLIENT_SNI, "%%ssl::>sni");
                DUMP_EXT_ACL_TYPE_FMT(SSL_SERVER_CERT_SUBJECT, "%%ssl::<cert_subject");
                DUMP_EXT_ACL_TYPE_FMT(SSL_SERVER_CERT_ISSUER, "%%ssl::<cert_issuer");
#endif
#if USE_AUTH
                DUMP_EXT_ACL_TYPE_FMT(USER_EXTERNAL," %%ue");
#endif
                DUMP_EXT_ACL_TYPE_FMT(EXT_LOG," %%ea");
                DUMP_EXT_ACL_TYPE_FMT(TAG," %%et");
                DUMP_EXT_ACL_TYPE_FMT(EXT_ACL_NAME," %%ACL");
                DUMP_EXT_ACL_TYPE_FMT(EXT_ACL_DATA," %%DATA");
                DUMP_EXT_ACL_TYPE_FMT(PERCENT, " %%%%");
            default:
                fatal("unknown external_acl format error");
                break;
            }
        }

        for (word = node->cmdline; word; word = word->next)
            storeAppendPrintf(sentry, " %s", word->key);

        storeAppendPrintf(sentry, "\n");
    }
}