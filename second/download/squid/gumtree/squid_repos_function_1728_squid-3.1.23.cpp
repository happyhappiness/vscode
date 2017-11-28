void
dump_externalAclHelper(StoreEntry * sentry, const char *name, const external_acl * list)
{
    const external_acl *node;
    const external_acl_format *format;
    const wordlist *word;

    for (node = list; node; node = node->next) {
        storeAppendPrintf(sentry, "%s %s", name, node->name);

        if (!node->local_addr.IsIPv6())
            storeAppendPrintf(sentry, " ipv4");
        else
            storeAppendPrintf(sentry, " ipv6");

        if (node->ttl != DEFAULT_EXTERNAL_ACL_TTL)
            storeAppendPrintf(sentry, " ttl=%d", node->ttl);

        if (node->negative_ttl != node->ttl)
            storeAppendPrintf(sentry, " negative_ttl=%d", node->negative_ttl);

        if (node->grace)
            storeAppendPrintf(sentry, " grace=%d", node->grace);

        if (node->children != DEFAULT_EXTERNAL_ACL_CHILDREN)
            storeAppendPrintf(sentry, " children=%d", node->children);

        if (node->concurrency)
            storeAppendPrintf(sentry, " concurrency=%d", node->concurrency);

        if (node->cache)
            storeAppendPrintf(sentry, " cache=%d", node->cache_size);

        for (format = node->format; format; format = format->next) {
            switch (format->type) {

            case _external_acl_format::EXT_ACL_HEADER_REQUEST:
            case _external_acl_format::EXT_ACL_HEADER_REQUEST_ID:
                storeAppendPrintf(sentry, " %%>{%s}", format->header);
                break;

            case _external_acl_format::EXT_ACL_HEADER_REQUEST_MEMBER:
            case _external_acl_format::EXT_ACL_HEADER_REQUEST_ID_MEMBER:
                storeAppendPrintf(sentry, " %%>{%s:%s}", format->header, format->member);
                break;

            case _external_acl_format::EXT_ACL_HEADER_REPLY:
            case _external_acl_format::EXT_ACL_HEADER_REPLY_ID:
                storeAppendPrintf(sentry, " %%<{%s}", format->header);
                break;

            case _external_acl_format::EXT_ACL_HEADER_REPLY_MEMBER:
            case _external_acl_format::EXT_ACL_HEADER_REPLY_ID_MEMBER:
                storeAppendPrintf(sentry, " %%<{%s:%s}", format->header, format->member);
                break;
#define DUMP_EXT_ACL_TYPE(a) \
            case _external_acl_format::EXT_ACL_##a: \
                storeAppendPrintf(sentry, " %%%s", #a); \
                break

#define DUMP_EXT_ACL_TYPE_FMT(a, fmt, ...) \
            case _external_acl_format::EXT_ACL_##a: \
                storeAppendPrintf(sentry, fmt, ##__VA_ARGS__); \
                break

                DUMP_EXT_ACL_TYPE(LOGIN);
#if USE_IDENT

                DUMP_EXT_ACL_TYPE(IDENT);
#endif

                DUMP_EXT_ACL_TYPE(SRC);
                DUMP_EXT_ACL_TYPE(SRCPORT);
                DUMP_EXT_ACL_TYPE(MYADDR);
                DUMP_EXT_ACL_TYPE(MYPORT);
                DUMP_EXT_ACL_TYPE(URI);
                DUMP_EXT_ACL_TYPE(DST);
                DUMP_EXT_ACL_TYPE(PROTO);
                DUMP_EXT_ACL_TYPE(PORT);
                DUMP_EXT_ACL_TYPE(PATH);
                DUMP_EXT_ACL_TYPE(METHOD);
#if USE_SSL
                DUMP_EXT_ACL_TYPE_FMT(USER_CERT_RAW, " %%USER_CERT_RAW");
                DUMP_EXT_ACL_TYPE_FMT(USER_CERTCHAIN_RAW, " %%USER_CERTCHAIN_RAW");
                DUMP_EXT_ACL_TYPE_FMT(USER_CERT, " %%USER_CERT_%s", format->header);
                DUMP_EXT_ACL_TYPE_FMT(CA_CERT, " %%CA_CERT_%s", format->header);
#endif

                DUMP_EXT_ACL_TYPE(EXT_USER);
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