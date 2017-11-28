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

