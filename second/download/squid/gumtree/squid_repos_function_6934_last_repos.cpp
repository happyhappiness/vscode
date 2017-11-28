void
Format::Format::assemble(MemBuf &mb, const AccessLogEntry::Pointer &al, int logSequenceNumber) const
{
    static char tmp[1024];
    SBuf sb;

    for (Token *fmt = format; fmt; fmt = fmt->next) {   /* for each token */
        const char *out = nullptr;
        int quote = 0;
        long int outint = 0;
        int doint = 0;
        int dofree = 0;
        int64_t outoff = 0;
        int dooff = 0;
        struct timeval outtv = {0, 0};
        int doMsec = 0;
        int doSec = 0;

        switch (fmt->type) {

        case LFT_NONE:
            out = "";
            break;

        case LFT_STRING:
            out = fmt->data.string;
            break;

        case LFT_CLIENT_IP_ADDRESS:
            al->getLogClientIp(tmp, sizeof(tmp));
            out = tmp;
            break;

        case LFT_CLIENT_FQDN:
            if (al->cache.caddr.isAnyAddr()) // e.g., ICAP OPTIONS lack client
                out = "-";
            else
                out = fqdncache_gethostbyaddr(al->cache.caddr, FQDN_LOOKUP_IF_MISS);

            if (!out) {
                out = al->cache.caddr.toStr(tmp, sizeof(tmp));
            }
            break;

        case LFT_CLIENT_PORT:
            if (al->request) {
                outint = al->request->client_addr.port();
                doint = 1;
            } else if (al->tcpClient) {
                outint = al->tcpClient->remote.port();
                doint = 1;
            }
            break;

        case LFT_CLIENT_EUI:
#if USE_SQUID_EUI
            // TODO make the ACL checklist have a direct link to any TCP details.
            if (al->request && al->request->clientConnectionManager.valid() &&
                    al->request->clientConnectionManager->clientConnection) {
                const auto &conn = al->request->clientConnectionManager->clientConnection;
                if (conn->remote.isIPv4())
                    conn->remoteEui48.encode(tmp, sizeof(tmp));
                else
                    conn->remoteEui64.encode(tmp, sizeof(tmp));
                out = tmp;
            }
#endif
            break;

        case LFT_EXT_ACL_CLIENT_EUI48:
#if USE_SQUID_EUI
            if (al->request && al->request->clientConnectionManager.valid() &&
                    al->request->clientConnectionManager->clientConnection &&
                    al->request->clientConnectionManager->clientConnection->remote.isIPv4()) {
                al->request->clientConnectionManager->clientConnection->remoteEui48.encode(tmp, sizeof(tmp));
                out = tmp;
            }
#endif
            break;

        case LFT_EXT_ACL_CLIENT_EUI64:
#if USE_SQUID_EUI
            if (al->request && al->request->clientConnectionManager.valid() &&
                    al->request->clientConnectionManager->clientConnection &&
                    !al->request->clientConnectionManager->clientConnection->remote.isIPv4()) {
                al->request->clientConnectionManager->clientConnection->remoteEui64.encode(tmp, sizeof(tmp));
                out = tmp;
            }
#endif
            break;

        case LFT_SERVER_IP_ADDRESS:
            if (al->hier.tcpServer)
                out = al->hier.tcpServer->remote.toStr(tmp, sizeof(tmp));
            break;

        case LFT_SERVER_FQDN_OR_PEER_NAME:
            out = al->hier.host;
            break;

        case LFT_SERVER_PORT:
            if (al->hier.tcpServer) {
                outint = al->hier.tcpServer->remote.port();
                doint = 1;
            }
            break;

        case LFT_LOCAL_LISTENING_IP: {
            // avoid logging a dash if we have reliable info
            const bool interceptedAtKnownPort = al->request ?
                                                (al->request->flags.interceptTproxy ||
                                                 al->request->flags.intercepted) && al->cache.port :
                                                false;
            if (interceptedAtKnownPort) {
                const bool portAddressConfigured = !al->cache.port->s.isAnyAddr();
                if (portAddressConfigured)
                    out = al->cache.port->s.toStr(tmp, sizeof(tmp));
            } else if (al->tcpClient)
                out = al->tcpClient->local.toStr(tmp, sizeof(tmp));
        }
        break;

        case LFT_CLIENT_LOCAL_IP:
            if (al->tcpClient)
                out = al->tcpClient->local.toStr(tmp, sizeof(tmp));
            break;

        case LFT_CLIENT_LOCAL_TOS:
            if (al->tcpClient) {
                sb.appendf("0x%x", static_cast<uint32_t>(al->tcpClient->tos));
                out = sb.c_str();
            }
            break;

        case LFT_CLIENT_LOCAL_NFMARK:
            if (al->tcpClient) {
                sb.appendf("0x%x", al->tcpClient->nfmark);
                out = sb.c_str();
            }
            break;

        case LFT_LOCAL_LISTENING_PORT:
            if (al->cache.port) {
                outint = al->cache.port->s.port();
                doint = 1;
            } else if (al->request) {
                outint = al->request->my_addr.port();
                doint = 1;
            }
            break;

        case LFT_CLIENT_LOCAL_PORT:
            if (al->tcpClient) {
                outint = al->tcpClient->local.port();
                doint = 1;
            }
            break;

        case LFT_SERVER_LOCAL_IP_OLD_27:
        case LFT_SERVER_LOCAL_IP:
            if (al->hier.tcpServer)
                out = al->hier.tcpServer->local.toStr(tmp, sizeof(tmp));
            break;

        case LFT_SERVER_LOCAL_PORT:
            if (al->hier.tcpServer) {
                outint = al->hier.tcpServer->local.port();
                doint = 1;
            }
            break;

        case LFT_SERVER_LOCAL_TOS:
            if (al->hier.tcpServer) {
                sb.appendf("0x%x", static_cast<uint32_t>(al->hier.tcpServer->tos));
                out = sb.c_str();
            }
            break;

        case LFT_SERVER_LOCAL_NFMARK:
            if (al->hier.tcpServer) {
                sb.appendf("0x%x", al->hier.tcpServer->nfmark);
                out = sb.c_str();
            }
            break;

        case LFT_TIME_SECONDS_SINCE_EPOCH:
            // some platforms store time in 32-bit, some 64-bit...
            outoff = static_cast<int64_t>(current_time.tv_sec);
            dooff = 1;
            break;

        case LFT_TIME_SUBSECOND:
            outint = current_time.tv_usec / fmt->divisor;
            doint = 1;
            break;

        case LFT_TIME_LOCALTIME:
        case LFT_TIME_GMT: {
            const char *spec;
            struct tm *t;
            spec = fmt->data.string;

            if (fmt->type == LFT_TIME_LOCALTIME) {
                if (!spec)
                    spec = "%d/%b/%Y:%H:%M:%S %z";
                t = localtime(&squid_curtime);
            } else {
                if (!spec)
                    spec = "%d/%b/%Y:%H:%M:%S";

                t = gmtime(&squid_curtime);
            }

            strftime(tmp, sizeof(tmp), spec, t);
            out = tmp;
        }
        break;

        case LFT_TIME_START:
            outtv = al->cache.start_time;
            doSec = 1;
            break;

        case LFT_TIME_TO_HANDLE_REQUEST:
            outtv = al->cache.trTime;
            doMsec = 1;
            break;

        case LFT_PEER_RESPONSE_TIME:
            if (al->hier.peer_response_time.tv_sec != -1) {
                outtv = al->hier.peer_response_time;
                doMsec = 1;
            }
            break;

        case LFT_TOTAL_SERVER_SIDE_RESPONSE_TIME: {
            timeval total_response_time;
            al->hier.totalResponseTime(total_response_time);
            if (total_response_time.tv_sec != -1) {
                outtv = total_response_time;
                doMsec = 1;
            }
        }
        break;

        case LFT_DNS_WAIT_TIME:
            if (al->request && al->request->dnsWait >= 0) {
                // TODO: microsecond precision for dns wait time.
                // Convert miliseconds to timeval struct:
                outtv.tv_sec = al->request->dnsWait / 1000;
                outtv.tv_usec = (al->request->dnsWait % 1000) * 1000;
                doMsec = 1;
            }
            break;

        case LFT_REQUEST_HEADER:
            if (const HttpMsg *msg = actualRequestHeader(al)) {
                sb = StringToSBuf(msg->header.getByName(fmt->data.header.header));
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_ADAPTED_REQUEST_HEADER:
            if (al->adapted_request) {
                sb = StringToSBuf(al->adapted_request->header.getByName(fmt->data.header.header));
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_REPLY_HEADER:
            if (const HttpMsg *msg = actualReplyHeader(al)) {
                sb = StringToSBuf(msg->header.getByName(fmt->data.header.header));
                out = sb.c_str();
                quote = 1;
            }
            break;

#if USE_ADAPTATION
        case LFT_ADAPTATION_SUM_XACT_TIMES:
            if (al->request) {
                Adaptation::History::Pointer ah = al->request->adaptHistory();
                if (ah) {
                    ah->sumLogString(fmt->data.string, sb);
                    out = sb.c_str();
                }
            }
            break;

        case LFT_ADAPTATION_ALL_XACT_TIMES:
            if (al->request) {
                Adaptation::History::Pointer ah = al->request->adaptHistory();
                if (ah) {
                    ah->allLogString(fmt->data.string, sb);
                    out = sb.c_str();
                }
            }
            break;

        case LFT_ADAPTATION_LAST_HEADER:
            if (al->request) {
                const Adaptation::History::Pointer ah = al->request->adaptHistory();
                if (ah) { // XXX: add adapt::<all_h but use lastMeta here
                    sb = StringToSBuf(ah->allMeta.getByName(fmt->data.header.header));
                    out = sb.c_str();
                    quote = 1;
                }
            }
            break;

        case LFT_ADAPTATION_LAST_HEADER_ELEM:
            if (al->request) {
                const Adaptation::History::Pointer ah = al->request->adaptHistory();
                if (ah) { // XXX: add adapt::<all_h but use lastMeta here
                    sb = StringToSBuf(ah->allMeta.getByNameListMember(fmt->data.header.header, fmt->data.header.element, fmt->data.header.separator));
                    out = sb.c_str();
                    quote = 1;
                }
            }
            break;

        case LFT_ADAPTATION_LAST_ALL_HEADERS:
            out = al->adapt.last_meta;
            quote = 1;
            break;
#endif

#if ICAP_CLIENT
        case LFT_ICAP_ADDR:
            out = al->icap.hostAddr.toStr(tmp, sizeof(tmp));
            break;

        case LFT_ICAP_SERV_NAME:
            out = al->icap.serviceName.termedBuf();
            break;

        case LFT_ICAP_REQUEST_URI:
            out = al->icap.reqUri.termedBuf();
            break;

        case LFT_ICAP_REQUEST_METHOD:
            out = Adaptation::Icap::ICAP::methodStr(al->icap.reqMethod);
            break;

        case LFT_ICAP_BYTES_SENT:
            outoff = al->icap.bytesSent;
            dooff = 1;
            break;

        case LFT_ICAP_BYTES_READ:
            outoff = al->icap.bytesRead;
            dooff = 1;
            break;

        case LFT_ICAP_BODY_BYTES_READ:
            if (al->icap.bodyBytesRead >= 0) {
                outoff = al->icap.bodyBytesRead;
                dooff = 1;
            }
            // else if icap.bodyBytesRead < 0, we do not have any http data,
            // so just print a "-" (204 responses etc)
            break;

        case LFT_ICAP_REQ_HEADER:
            if (al->icap.request) {
                sb = StringToSBuf(al->icap.request->header.getByName(fmt->data.header.header));
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_ICAP_REQ_HEADER_ELEM:
            if (al->icap.request) {
                sb = StringToSBuf(al->icap.request->header.getByNameListMember(fmt->data.header.header, fmt->data.header.element, fmt->data.header.separator));
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_ICAP_REQ_ALL_HEADERS:
            if (al->icap.request) {
                HttpHeaderPos pos = HttpHeaderInitPos;
                while (const HttpHeaderEntry *e = al->icap.request->header.getEntry(&pos)) {
                    sb.append(StringToSBuf(e->name));
                    sb.append(": ");
                    sb.append(StringToSBuf(e->value));
                    sb.append("\r\n");
                }
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_ICAP_REP_HEADER:
            if (al->icap.reply) {
                sb = StringToSBuf(al->icap.reply->header.getByName(fmt->data.header.header));
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_ICAP_REP_HEADER_ELEM:
            if (al->icap.reply) {
                sb = StringToSBuf(al->icap.reply->header.getByNameListMember(fmt->data.header.header, fmt->data.header.element, fmt->data.header.separator));
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_ICAP_REP_ALL_HEADERS:
            if (al->icap.reply) {
                HttpHeaderPos pos = HttpHeaderInitPos;
                while (const HttpHeaderEntry *e = al->icap.reply->header.getEntry(&pos)) {
                    sb.append(StringToSBuf(e->name));
                    sb.append(": ");
                    sb.append(StringToSBuf(e->value));
                    sb.append("\r\n");
                }
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_ICAP_TR_RESPONSE_TIME:
            outtv = al->icap.trTime;
            doMsec = 1;
            break;

        case LFT_ICAP_IO_TIME:
            outtv = al->icap.ioTime;
            doMsec = 1;
            break;

        case LFT_ICAP_STATUS_CODE:
            outint = al->icap.resStatus;
            doint  = 1;
            break;

        case LFT_ICAP_OUTCOME:
            out = al->icap.outcome;
            break;

        case LFT_ICAP_TOTAL_TIME:
            outtv = al->icap.processingTime;
            doMsec = 1;
            break;
#endif
        case LFT_REQUEST_HEADER_ELEM:
            if (const HttpMsg *msg = actualRequestHeader(al)) {
                sb = StringToSBuf(msg->header.getByNameListMember(fmt->data.header.header, fmt->data.header.element, fmt->data.header.separator));
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_ADAPTED_REQUEST_HEADER_ELEM:
            if (al->adapted_request) {
                sb = StringToSBuf(al->adapted_request->header.getByNameListMember(fmt->data.header.header, fmt->data.header.element, fmt->data.header.separator));
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_REPLY_HEADER_ELEM:
            if (const HttpMsg *msg = actualReplyHeader(al)) {
                sb = StringToSBuf(msg->header.getByNameListMember(fmt->data.header.header, fmt->data.header.element, fmt->data.header.separator));
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_REQUEST_ALL_HEADERS:
#if ICAP_CLIENT
            if (al->icap.reqMethod == Adaptation::methodRespmod) {
                // XXX: since AccessLogEntry::Headers lacks virgin response
                // headers, do nothing for now
                out = nullptr;
            } else
#endif
            {
                out = al->headers.request;
                quote = 1;
            }
            break;

        case LFT_ADAPTED_REQUEST_ALL_HEADERS:
            out = al->headers.adapted_request;
            quote = 1;
            break;

        case LFT_REPLY_ALL_HEADERS:
            out = al->headers.reply;
#if ICAP_CLIENT
            if (!out && al->icap.reqMethod == Adaptation::methodReqmod)
                out = al->headers.adapted_request;
#endif
            quote = 1;
            break;

        case LFT_USER_NAME:
#if USE_AUTH
            if (al->request && al->request->auth_user_request)
                out = strOrNull(al->request->auth_user_request->username());
#endif
            if (!out && al->request && al->request->extacl_user.size()) {
                if (const char *t = al->request->extacl_user.termedBuf())
                    out = t;
            }
            if (!out)
                out = strOrNull(al->cache.extuser);
#if USE_OPENSSL
            if (!out)
                out = strOrNull(al->cache.ssluser);
#endif
            if (!out)
                out = strOrNull(al->cache.rfc931);
            break;

        case LFT_USER_LOGIN:
#if USE_AUTH
            if (al->request && al->request->auth_user_request)
                out = strOrNull(al->request->auth_user_request->username());
#endif
            break;

        case LFT_USER_IDENT:
            out = strOrNull(al->cache.rfc931);
            break;

        case LFT_USER_EXTERNAL:
            if (al->request && al->request->extacl_user.size()) {
                if (const char *t = al->request->extacl_user.termedBuf())
                    out = t;
            }

            if (!out)
                out = strOrNull(al->cache.extuser);
            break;

        /* case LFT_USER_REALM: */
        /* case LFT_USER_SCHEME: */

        // the fmt->type can not be LFT_HTTP_SENT_STATUS_CODE_OLD_30
        // but compiler complains if ommited
        case LFT_HTTP_SENT_STATUS_CODE_OLD_30:
        case LFT_HTTP_SENT_STATUS_CODE:
            outint = al->http.code;
            doint = 1;
            break;

        case LFT_HTTP_RECEIVED_STATUS_CODE:
            if (al->hier.peer_reply_status != Http::scNone) {
                outint = al->hier.peer_reply_status;
                doint = 1;
            }
            break;
        /* case LFT_HTTP_STATUS:
         *           out = statusline->text;
         *     quote = 1;
         *     break;
         */
        case LFT_HTTP_BODY_BYTES_READ:
            if (al->hier.bodyBytesRead >= 0) {
                outoff = al->hier.bodyBytesRead;
                dooff = 1;
            }
            // else if hier.bodyBytesRead < 0 we did not have any data exchange with
            // a peer server so just print a "-" (eg requests served from cache,
            // or internal error messages).
            break;

        case LFT_SQUID_STATUS:
            out = al->cache.code.c_str();
            break;

        case LFT_SQUID_ERROR:
            if (al->request && al->request->errType != ERR_NONE)
                out = errorPageName(al->request->errType);
            break;

        case LFT_SQUID_ERROR_DETAIL:
#if USE_OPENSSL
            if (al->request && al->request->errType == ERR_SECURE_CONNECT_FAIL) {
                out = Ssl::GetErrorName(al->request->errDetail);
                if (!out)
                    out = sslErrorName(al->request->errDetail, tmp, sizeof(tmp));
            } else
#endif
                if (al->request && al->request->errDetail != ERR_DETAIL_NONE) {
                    if (al->request->errDetail > ERR_DETAIL_START && al->request->errDetail < ERR_DETAIL_MAX)
                        out = errorDetailName(al->request->errDetail);
                    else {
                        if (al->request->errDetail >= ERR_DETAIL_EXCEPTION_START)
                            sb.appendf("%s=0x%X",
                                       errorDetailName(al->request->errDetail), (uint32_t) al->request->errDetail);
                        else
                            sb.appendf("%s=%d",
                                       errorDetailName(al->request->errDetail), al->request->errDetail);
                        out = sb.c_str();
                    }
                }
            break;

        case LFT_SQUID_HIERARCHY:
            if (al->hier.ping.timedout)
                mb.append("TIMEOUT_", 8);
            out = hier_code_str[al->hier.code];
            break;

        case LFT_MIME_TYPE:
            out = al->http.content_type;
            break;

        case LFT_CLIENT_REQ_METHOD:
            if (al->request) {
                sb = al->request->method.image();
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_CLIENT_REQ_URI:
            // original client URI
            if (al->request) {
                sb = al->request->effectiveRequestUri();
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_CLIENT_REQ_URLSCHEME:
            if (al->request) {
                sb = al->request->url.getScheme().image();
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_CLIENT_REQ_URLDOMAIN:
            if (al->request) {
                out = al->request->url.host();
                quote = 1;
            }
            break;

        case LFT_CLIENT_REQ_URLPORT:
            if (al->request) {
                outint = al->request->url.port();
                doint = 1;
            }
            break;

        case LFT_REQUEST_URLPATH_OLD_31:
        case LFT_CLIENT_REQ_URLPATH:
            if (al->request) {
                sb = al->request->url.path();
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_CLIENT_REQ_VERSION:
            if (al->request) {
                sb.appendf("%u.%u", al->request->http_ver.major, al->request->http_ver.minor);
                out = sb.c_str();
            }
            break;

        case LFT_REQUEST_METHOD:
            sb = al->getLogMethod();
            out = sb.c_str();
            quote = 1;
            break;

        case LFT_REQUEST_URI:
            if (!al->url.isEmpty()) {
                sb = al->url;
                out = sb.c_str();
            }
            break;

        case LFT_REQUEST_VERSION_OLD_2X:
        case LFT_REQUEST_VERSION:
            sb.appendf("%u.%u", al->http.version.major, al->http.version.minor);
            out = sb.c_str();
            break;

        case LFT_SERVER_REQ_METHOD:
            if (al->adapted_request) {
                sb = al->adapted_request->method.image();
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_SERVER_REQ_URI:
            // adapted request URI sent to server/peer
            if (al->adapted_request) {
                sb = al->adapted_request->effectiveRequestUri();
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_SERVER_REQ_URLSCHEME:
            if (al->adapted_request) {
                sb = al->adapted_request->url.getScheme().image();
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_SERVER_REQ_URLDOMAIN:
            if (al->adapted_request) {
                out = al->adapted_request->url.host();
                quote = 1;
            }
            break;

        case LFT_SERVER_REQ_URLPORT:
            if (al->adapted_request) {
                outint = al->adapted_request->url.port();
                doint = 1;
            }
            break;

        case LFT_SERVER_REQ_URLPATH:
            if (al->adapted_request) {
                sb = al->adapted_request->url.path();
                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_SERVER_REQ_VERSION:
            if (al->adapted_request) {
                sb.appendf("%u.%u",
                           al->adapted_request->http_ver.major,
                           al->adapted_request->http_ver.minor);
                out = tmp;
            }
            break;

        case LFT_CLIENT_REQUEST_SIZE_TOTAL:
            outoff = al->http.clientRequestSz.messageTotal();
            dooff = 1;
            break;

        case LFT_CLIENT_REQUEST_SIZE_HEADERS:
            outoff = al->http.clientRequestSz.header;
            dooff =1;
            break;

        /*case LFT_REQUEST_SIZE_BODY: */
        /*case LFT_REQUEST_SIZE_BODY_NO_TE: */

        case LFT_ADAPTED_REPLY_SIZE_TOTAL:
            outoff = al->http.clientReplySz.messageTotal();
            dooff = 1;
            break;

        case LFT_REPLY_HIGHOFFSET:
            outoff = al->cache.highOffset;
            dooff = 1;
            break;

        case LFT_REPLY_OBJECTSIZE:
            outoff = al->cache.objectSize;
            dooff = 1;
            break;

        case LFT_ADAPTED_REPLY_SIZE_HEADERS:
            outint = al->http.clientReplySz.header;
            doint = 1;
            break;

        /*case LFT_REPLY_SIZE_BODY: */
        /*case LFT_REPLY_SIZE_BODY_NO_TE: */

        case LFT_CLIENT_IO_SIZE_TOTAL:
            outint = al->http.clientRequestSz.messageTotal() + al->http.clientReplySz.messageTotal();
            doint = 1;
            break;
        /*case LFT_SERVER_IO_SIZE_TOTAL: */

        case LFT_TAG:
            if (al->request) {
                out = al->request->tag.termedBuf();
                quote = 1;
            }
            break;

        case LFT_EXT_LOG:
            if (al->request) {
                out = al->request->extacl_log.termedBuf();
                quote = 1;
            }
            break;

        case LFT_SEQUENCE_NUMBER:
            outoff = logSequenceNumber;
            dooff = 1;
            break;

#if USE_OPENSSL
        case LFT_SSL_BUMP_MODE: {
            const Ssl::BumpMode mode = static_cast<Ssl::BumpMode>(al->ssl.bumpMode);
            // for Ssl::bumpEnd, Ssl::bumpMode() returns NULL and we log '-'
            out = Ssl::bumpMode(mode);
        }
        break;

        case LFT_EXT_ACL_USER_CERT_RAW:
            if (al->request) {
                ConnStateData *conn = al->request->clientConnectionManager.get();
                if (conn && Comm::IsConnOpen(conn->clientConnection)) {
                    if (auto ssl = fd_table[conn->clientConnection->fd].ssl.get())
                        out = sslGetUserCertificatePEM(ssl);
                }
            }
            break;

        case LFT_EXT_ACL_USER_CERTCHAIN_RAW:
            if (al->request) {
                ConnStateData *conn = al->request->clientConnectionManager.get();
                if (conn && Comm::IsConnOpen(conn->clientConnection)) {
                    if (auto ssl = fd_table[conn->clientConnection->fd].ssl.get())
                        out = sslGetUserCertificatePEM(ssl);
                }
            }
            break;

        case LFT_EXT_ACL_USER_CERT:
            if (al->request) {
                ConnStateData *conn = al->request->clientConnectionManager.get();
                if (conn && Comm::IsConnOpen(conn->clientConnection)) {
                    if (auto ssl = fd_table[conn->clientConnection->fd].ssl.get())
                        out = sslGetUserAttribute(ssl, format->data.header.header);
                }
            }
            break;

        case LFT_EXT_ACL_USER_CA_CERT:
            if (al->request) {
                ConnStateData *conn = al->request->clientConnectionManager.get();
                if (conn && Comm::IsConnOpen(conn->clientConnection)) {
                    if (auto ssl = fd_table[conn->clientConnection->fd].ssl.get())
                        out = sslGetCAAttribute(ssl, format->data.header.header);
                }
            }
            break;

        case LFT_SSL_USER_CERT_SUBJECT:
            if (X509 *cert = al->cache.sslClientCert.get()) {
                if (X509_NAME *subject = X509_get_subject_name(cert)) {
                    X509_NAME_oneline(subject, tmp, sizeof(tmp));
                    out = tmp;
                }
            }
            break;

        case LFT_SSL_USER_CERT_ISSUER:
            if (X509 *cert = al->cache.sslClientCert.get()) {
                if (X509_NAME *issuer = X509_get_issuer_name(cert)) {
                    X509_NAME_oneline(issuer, tmp, sizeof(tmp));
                    out = tmp;
                }
            }
            break;

        case LFT_SSL_CLIENT_SNI:
            if (al->request && al->request->clientConnectionManager.valid()) {
                if (const ConnStateData *conn = al->request->clientConnectionManager.get()) {
                    if (!conn->tlsClientSni().isEmpty()) {
                        sb = conn->tlsClientSni();
                        out = sb.c_str();
                    }
                }
            }
            break;

        case LFT_SSL_SERVER_CERT_ERRORS:
            if (al->request && al->request->clientConnectionManager.valid()) {
                if (Ssl::ServerBump * srvBump = al->request->clientConnectionManager->serverBump()) {
                    const char *separator = fmt->data.string ? fmt->data.string : ":";
                    for (const Security::CertErrors *sslError = srvBump->sslErrors(); sslError; sslError = sslError->next) {
                        if (!sb.isEmpty())
                            sb.append(separator);
                        if (const char *errorName = Ssl::GetErrorName(sslError->element.code))
                            sb.append(errorName);
                        else
                            sb.append(sslErrorName(sslError->element.code, tmp, sizeof(tmp)));
                        if (sslError->element.depth >= 0)
                            sb.appendf("@depth=%d", sslError->element.depth);
                    }
                    if (!sb.isEmpty())
                        out = sb.c_str();
                }
            }
            break;

        case LFT_SSL_SERVER_CERT_ISSUER:
        case LFT_SSL_SERVER_CERT_SUBJECT:
            if (al->request && al->request->clientConnectionManager.valid()) {
                if (Ssl::ServerBump * srvBump = al->request->clientConnectionManager->serverBump()) {
                    if (X509 *serverCert = srvBump->serverCert.get()) {
                        if (fmt->type == LFT_SSL_SERVER_CERT_SUBJECT)
                            out = Ssl::GetX509UserAttribute(serverCert, "DN");
                        else
                            out = Ssl::GetX509CAAttribute(serverCert, "DN");
                    }
                }
            }
            break;

        case LFT_TLS_CLIENT_NEGOTIATED_VERSION:
            if (al->tcpClient && al->tcpClient->hasTlsNegotiations())
                out = al->tcpClient->hasTlsNegotiations()->negotiatedVersion();
            break;

        case LFT_TLS_SERVER_NEGOTIATED_VERSION:
            if (al->hier.tcpServer && al->hier.tcpServer->hasTlsNegotiations())
                out = al->hier.tcpServer->hasTlsNegotiations()->negotiatedVersion();
            break;

        case LFT_TLS_CLIENT_RECEIVED_HELLO_VERSION:
            if (al->tcpClient && al->tcpClient->hasTlsNegotiations())
                out = al->tcpClient->hasTlsNegotiations()->helloVersion();
            break;

        case LFT_TLS_SERVER_RECEIVED_HELLO_VERSION:
            if (al->hier.tcpServer && al->hier.tcpServer->hasTlsNegotiations())
                out = al->hier.tcpServer->hasTlsNegotiations()->helloVersion();
            break;

        case LFT_TLS_CLIENT_SUPPORTED_VERSION:
            if (al->tcpClient && al->tcpClient->hasTlsNegotiations())
                out = al->tcpClient->hasTlsNegotiations()->supportedVersion();
            break;

        case LFT_TLS_SERVER_SUPPORTED_VERSION:
            if (al->hier.tcpServer && al->hier.tcpServer->hasTlsNegotiations())
                out = al->hier.tcpServer->hasTlsNegotiations()->supportedVersion();
            break;

        case LFT_TLS_CLIENT_NEGOTIATED_CIPHER:
            if (al->tcpClient && al->tcpClient->hasTlsNegotiations())
                out = al->tcpClient->hasTlsNegotiations()->cipherName();
            break;

        case LFT_TLS_SERVER_NEGOTIATED_CIPHER:
            if (al->hier.tcpServer && al->hier.tcpServer->hasTlsNegotiations())
                out = al->hier.tcpServer->hasTlsNegotiations()->cipherName();
            break;
#endif

        case LFT_REQUEST_URLGROUP_OLD_2X:
            assert(LFT_REQUEST_URLGROUP_OLD_2X == 0); // should never happen.

        case LFT_NOTE:
            tmp[0] = fmt->data.header.separator;
            tmp[1] = '\0';
            if (fmt->data.header.header && *fmt->data.header.header) {
                const char *separator = tmp;
#if USE_ADAPTATION
                Adaptation::History::Pointer ah = al->request ? al->request->adaptHistory() : Adaptation::History::Pointer();
                if (ah && ah->metaHeaders) {
                    if (const char *meta = ah->metaHeaders->find(fmt->data.header.header, separator))
                        sb.append(meta);
                }
#endif
                if (al->notes) {
                    if (const char *note = al->notes->find(fmt->data.header.header, separator)) {
                        if (!sb.isEmpty())
                            sb.append(separator);
                        sb.append(note);
                    }
                }
                out = sb.c_str();
                quote = 1;
            } else {
                // if no argument given use default "\r\n" as notes separator
                const char *separator = fmt->data.string ? tmp : "\r\n";
#if USE_ADAPTATION
                Adaptation::History::Pointer ah = al->request ? al->request->adaptHistory() : Adaptation::History::Pointer();
                if (ah && ah->metaHeaders && !ah->metaHeaders->empty())
                    sb.append(ah->metaHeaders->toString(separator));
#endif
                if (al->notes && !al->notes->empty())
                    sb.append(al->notes->toString(separator));

                out = sb.c_str();
                quote = 1;
            }
            break;

        case LFT_CREDENTIALS:
#if USE_AUTH
            if (al->request && al->request->auth_user_request)
                out = strOrNull(al->request->auth_user_request->credentialsStr());
#endif
            break;

        case LFT_PERCENT:
            out = "%";
            break;

        case LFT_EXT_ACL_NAME:
            out = al->lastAclName;
            break;

        case LFT_EXT_ACL_DATA:
            if (!al->lastAclData.isEmpty())
                out = al->lastAclData.c_str();
            break;
        }

        if (dooff) {
            sb.appendf("%0*" PRId64, fmt->zero && fmt->widthMin >= 0 ? fmt->widthMin : 0, outoff);
            out = sb.c_str();

        } else if (doint) {
            sb.appendf("%0*ld", fmt->zero && fmt->widthMin >= 0 ? fmt->widthMin : 0, outint);
            out = sb.c_str();
        } else if (doMsec) {
            if (fmt->widthMax < 0) {
                sb.appendf("%0*ld", fmt->widthMin , tvToMsec(outtv));
            } else {
                int precision = fmt->widthMax;
                sb.appendf("%0*" PRId64 ".%0*" PRId64 "", fmt->zero && (fmt->widthMin - precision - 1 >= 0) ? fmt->widthMin - precision - 1 : 0, static_cast<int64_t>(outtv.tv_sec * 1000 + outtv.tv_usec / 1000), precision, static_cast<int64_t>((outtv.tv_usec % 1000 )* (1000 / fmt->divisor)));
            }
            out = sb.c_str();
        } else if (doSec) {
            int precision = fmt->widthMax >=0 ? fmt->widthMax :3;
            sb.appendf("%0*" PRId64 ".%0*d", fmt->zero && (fmt->widthMin - precision - 1 >= 0) ? fmt->widthMin - precision - 1 : 0, static_cast<int64_t>(outtv.tv_sec), precision, (int)(outtv.tv_usec / fmt->divisor));
            out = sb.c_str();
        }

        if (out && *out) {
            if (quote || fmt->quote != LOG_QUOTE_NONE) {
                // Do not write to the tmp buffer because it may contain the to-be-quoted value.
                static char quotedOut[2 * sizeof(tmp)];
                static_assert(sizeof(quotedOut) > 0, "quotedOut has zero length");
                quotedOut[0] = '\0';

                char *newout = NULL;
                int newfree = 0;

                switch (fmt->quote) {

                case LOG_QUOTE_NONE:
                    newout = rfc1738_escape_unescaped(out);
                    break;

                case LOG_QUOTE_QUOTES: {
                    size_t out_len = static_cast<size_t>(strlen(out)) * 2 + 1;
                    if (out_len >= sizeof(tmp)) {
                        newout = (char *)xmalloc(out_len);
                        newfree = 1;
                    } else
                        newout = quotedOut;
                    log_quoted_string(out, newout);
                }
                break;

                case LOG_QUOTE_MIMEBLOB:
                    newout = QuoteMimeBlob(out);
                    newfree = 1;
                    break;

                case LOG_QUOTE_URL:
                    newout = rfc1738_escape(out);
                    break;

                case LOG_QUOTE_SHELL: {
                    MemBuf mbq;
                    mbq.init();
                    strwordquote(&mbq, out);
                    newout = mbq.content();
                    mbq.stolen = 1;
                    newfree = 1;
                }
                break;

                case LOG_QUOTE_RAW:
                    break;
                }

                if (newout) {
                    if (dofree)
                        safe_free(out);

                    out = newout;

                    dofree = newfree;
                }
            }

            // enforce width limits if configured
            const bool haveMaxWidth = fmt->widthMax >=0 && !doint && !dooff && !doMsec && !doSec;
            if (haveMaxWidth || fmt->widthMin) {
                const int minWidth = fmt->widthMin >= 0 ?
                                     fmt->widthMin :0;
                const int maxWidth = haveMaxWidth ?
                                     fmt->widthMax : strlen(out);

                if (fmt->left)
                    mb.appendf("%-*.*s", minWidth, maxWidth, out);
                else
                    mb.appendf("%*.*s", minWidth, maxWidth, out);
            } else
                mb.append(out, strlen(out));
        } else {
            mb.append("-", 1);
        }

        if (fmt->space)
            mb.append(" ", 1);

        sb.clear();

        if (dofree)
            safe_free(out);
    }
}