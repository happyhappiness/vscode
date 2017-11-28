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
