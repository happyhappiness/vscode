            }
            break;
#if USE_SSL

        case _external_acl_format::EXT_ACL_USER_CERT_RAW:

            if (ch->conn() != NULL) {
                SSL *ssl = fd_table[ch->conn()->fd].ssl;

                if (ssl)
                    str = sslGetUserCertificatePEM(ssl);
            }

            break;

        case _external_acl_format::EXT_ACL_USER_CERTCHAIN_RAW:

            if (ch->conn() != NULL) {
                SSL *ssl = fd_table[ch->conn()->fd].ssl;

                if (ssl)
                    str = sslGetUserCertificateChainPEM(ssl);
            }

            break;

        case _external_acl_format::EXT_ACL_USER_CERT:

            if (ch->conn() != NULL) {
                SSL *ssl = fd_table[ch->conn()->fd].ssl;

                if (ssl)
                    str = sslGetUserAttribute(ssl, format->header);
            }

            break;

        case _external_acl_format::EXT_ACL_CA_CERT:

            if (ch->conn() != NULL) {
                SSL *ssl = fd_table[ch->conn()->fd].ssl;

                if (ssl)
                    str = sslGetCAAttribute(ssl, format->header);
            }

            break;
#endif

        case _external_acl_format::EXT_ACL_EXT_USER:
            str = request->extacl_user.termedBuf();
            break;

        case _external_acl_format::EXT_ACL_PERCENT:
            str = "%";
            break;

        case _external_acl_format::EXT_ACL_UNKNOWN:

        case _external_acl_format::EXT_ACL_END:
            fatal("unknown external_acl format error");
            break;
        }
