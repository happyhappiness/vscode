static char *
makeExternalAclKey(ACLFilledChecklist * ch, external_acl_data * acl_data)
{
    static MemBuf mb;
    char buf[256];
    int first = 1;
    wordlist *arg;
    external_acl_format *format;
    HttpRequest *request = ch->request;
    HttpReply *reply = ch->reply;
    mb.reset();
    bool data_used = false;

    for (format = acl_data->def->format; format; format = format->next) {
        const char *str = NULL;
        String sb;

        switch (format->type) {
#if USE_AUTH
        case _external_acl_format::EXT_ACL_LOGIN:
            // if this ACL line was the cause of credentials fetch
            // they may not already be in the checklist
            if (ch->auth_user_request == NULL && ch->request)
                ch->auth_user_request = ch->request->auth_user_request;

            if (ch->auth_user_request != NULL)
                str = ch->auth_user_request->username();
            break;
#endif
#if USE_IDENT
        case _external_acl_format::EXT_ACL_IDENT:
            str = ch->rfc931;

            if (!str || !*str) {
                ch->changeState(IdentLookup::Instance());
                return NULL;
            }

            break;
#endif

        case _external_acl_format::EXT_ACL_SRC:
            str = ch->src_addr.NtoA(buf,sizeof(buf));
            break;

        case _external_acl_format::EXT_ACL_SRCPORT:
            snprintf(buf, sizeof(buf), "%d", request->client_addr.GetPort());
            str = buf;
            break;

#if USE_SQUID_EUI
        case _external_acl_format::EXT_ACL_SRCEUI48:
            if (request->clientConnectionManager.valid() && request->clientConnectionManager->clientConnection != NULL &&
                    request->clientConnectionManager->clientConnection->remoteEui48.encode(buf, sizeof(buf)))
                str = buf;
            break;

        case _external_acl_format::EXT_ACL_SRCEUI64:
            if (request->clientConnectionManager.valid() && request->clientConnectionManager->clientConnection != NULL &&
                    request->clientConnectionManager->clientConnection->remoteEui64.encode(buf, sizeof(buf)))
                str = buf;
            break;
#endif

        case _external_acl_format::EXT_ACL_MYADDR:
            str = request->my_addr.NtoA(buf, sizeof(buf));
            break;

        case _external_acl_format::EXT_ACL_MYPORT:
            snprintf(buf, sizeof(buf), "%d", request->my_addr.GetPort());
            str = buf;
            break;

        case _external_acl_format::EXT_ACL_URI:
            str = urlCanonical(request);
            break;

        case _external_acl_format::EXT_ACL_DST:
            str = request->GetHost();
            break;

        case _external_acl_format::EXT_ACL_PROTO:
            str = AnyP::ProtocolType_str[request->protocol];
            break;

        case _external_acl_format::EXT_ACL_PORT:
            snprintf(buf, sizeof(buf), "%d", request->port);
            str = buf;
            break;

        case _external_acl_format::EXT_ACL_PATH:
            str = request->urlpath.termedBuf();
            break;

        case _external_acl_format::EXT_ACL_METHOD:
            str = RequestMethodStr(request->method);
            break;

        case _external_acl_format::EXT_ACL_HEADER_REQUEST:
            sb = request->header.getByName(format->header);
            str = sb.termedBuf();
            break;

        case _external_acl_format::EXT_ACL_HEADER_REQUEST_ID:
            sb = request->header.getStrOrList(format->header_id);
            str = sb.termedBuf();
            break;

        case _external_acl_format::EXT_ACL_HEADER_REQUEST_MEMBER:
            sb = request->header.getByNameListMember(format->header, format->member, format->separator);
            str = sb.termedBuf();
            break;

        case _external_acl_format::EXT_ACL_HEADER_REQUEST_ID_MEMBER:
            sb = request->header.getListMember(format->header_id, format->member, format->separator);
            str = sb.termedBuf();
            break;

        case _external_acl_format::EXT_ACL_HEADER_REPLY:
            if (reply) {
                sb = reply->header.getByName(format->header);
                str = sb.termedBuf();
            }
            break;

        case _external_acl_format::EXT_ACL_HEADER_REPLY_ID:
            if (reply) {
                sb = reply->header.getStrOrList(format->header_id);
                str = sb.termedBuf();
            }
            break;

        case _external_acl_format::EXT_ACL_HEADER_REPLY_MEMBER:
            if (reply) {
                sb = reply->header.getByNameListMember(format->header, format->member, format->separator);
                str = sb.termedBuf();
            }
            break;

        case _external_acl_format::EXT_ACL_HEADER_REPLY_ID_MEMBER:
            if (reply) {
                sb = reply->header.getListMember(format->header_id, format->member, format->separator);
                str = sb.termedBuf();
            }
            break;
#if USE_SSL

        case _external_acl_format::EXT_ACL_USER_CERT_RAW:

            if (ch->conn() != NULL && Comm::IsConnOpen(ch->conn()->clientConnection)) {
                SSL *ssl = fd_table[ch->conn()->clientConnection->fd].ssl;

                if (ssl)
                    str = sslGetUserCertificatePEM(ssl);
            }

            break;

        case _external_acl_format::EXT_ACL_USER_CERTCHAIN_RAW:

            if (ch->conn() != NULL && Comm::IsConnOpen(ch->conn()->clientConnection)) {
                SSL *ssl = fd_table[ch->conn()->clientConnection->fd].ssl;

                if (ssl)
                    str = sslGetUserCertificateChainPEM(ssl);
            }

            break;

        case _external_acl_format::EXT_ACL_USER_CERT:

            if (ch->conn() != NULL && Comm::IsConnOpen(ch->conn()->clientConnection)) {
                SSL *ssl = fd_table[ch->conn()->clientConnection->fd].ssl;

                if (ssl)
                    str = sslGetUserAttribute(ssl, format->header);
            }

            break;

        case _external_acl_format::EXT_ACL_USER_CA_CERT:

            if (ch->conn() != NULL && Comm::IsConnOpen(ch->conn()->clientConnection)) {
                SSL *ssl = fd_table[ch->conn()->clientConnection->fd].ssl;

                if (ssl)
                    str = sslGetCAAttribute(ssl, format->header);
            }

            break;
#endif
#if USE_AUTH
        case _external_acl_format::EXT_ACL_EXT_USER:
            str = request->extacl_user.termedBuf();
            break;
#endif
        case _external_acl_format::EXT_ACL_EXT_LOG:
            str = request->extacl_log.termedBuf();
            break;
        case _external_acl_format::EXT_ACL_TAG:
            str = request->tag.termedBuf();
            break;
        case _external_acl_format::EXT_ACL_ACLNAME:
            str = acl_data->name;
            break;
        case _external_acl_format::EXT_ACL_ACLDATA:
            data_used = true;
            for (arg = acl_data->arguments; arg; arg = arg->next) {
                if (!first)
                    sb.append(" ", 1);

                if (acl_data->def->quote == external_acl::QUOTE_METHOD_URL) {
                    const char *quoted = rfc1738_escape(arg->key);
                    sb.append(quoted, strlen(quoted));
                } else {
                    static MemBuf mb2;
                    mb2.init();
                    strwordquote(&mb2, arg->key);
                    sb.append(mb2.buf, mb2.size);
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

        if (!str)
            str = "-";

        if (!first)
            mb.append(" ", 1);

        if (acl_data->def->quote == external_acl::QUOTE_METHOD_URL) {
            const char *quoted = rfc1738_escape(str);
            mb.append(quoted, strlen(quoted));
        } else {
            strwordquote(&mb, str);
        }

        sb.clean();

        first = 0;
    }

    if (!data_used) {
        for (arg = acl_data->arguments; arg; arg = arg->next) {
            if (!first)
                mb.append(" ", 1);

            if (acl_data->def->quote == external_acl::QUOTE_METHOD_URL) {
                const char *quoted = rfc1738_escape(arg->key);
                mb.append(quoted, strlen(quoted));
            } else {
                strwordquote(&mb, arg->key);
            }

            first = 0;
        }
    }

    return mb.buf;
}