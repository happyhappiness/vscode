                    mb2.clean();
                }

                first = 0;
            }
            break;
        case _external_acl_format::EXT_ACL_PERCENT:
            str = "%";
            break;
        case _external_acl_format::EXT_ACL_UNKNOWN:

        case _external_acl_format::EXT_ACL_END:
            fatal("unknown external_acl format error");
            break;
        }

        if (str)
            if (!*str)
                str = NULL;
