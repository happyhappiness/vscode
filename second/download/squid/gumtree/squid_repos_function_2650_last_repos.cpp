const char *
ErrorState::Convert(char token, bool building_deny_info_url, bool allowRecursion)
{
    static MemBuf mb;
    const char *p = NULL;   /* takes priority over mb if set */
    int do_quote = 1;
    int no_urlescape = 0;       /* if true then item is NOT to be further URL-encoded */
    char ntoabuf[MAX_IPSTRLEN];

    mb.reset();

    switch (token) {

    case 'a':
#if USE_AUTH
        if (request && request->auth_user_request != NULL)
            p = request->auth_user_request->username();
        if (!p)
#endif
            p = "-";
        break;

    case 'b':
        mb.appendf("%u", getMyPort());
        break;

    case 'B':
        if (building_deny_info_url) break;
        if (request) {
            const SBuf &tmp = Ftp::UrlWith2f(request);
            mb.append(tmp.rawContent(), tmp.length());
        } else
            p = "[no URL]";
        break;

    case 'c':
        if (building_deny_info_url) break;
        p = errorPageName(type);
        break;

    case 'D':
        if (!allowRecursion)
            p = "%D";  // if recursion is not allowed, do not convert
#if USE_OPENSSL
        // currently only SSL error details implemented
        else if (detail) {
            detail->useRequest(request);
            const String &errDetail = detail->toString();
            if (errDetail.size() > 0) {
                MemBuf *detail_mb  = ConvertText(errDetail.termedBuf(), false);
                mb.append(detail_mb->content(), detail_mb->contentSize());
                delete detail_mb;
                do_quote = 0;
            }
        }
#endif
        if (!mb.contentSize())
            mb.append("[No Error Detail]", 17);
        break;

    case 'e':
        mb.appendf("%d", xerrno);
        break;

    case 'E':
        if (xerrno)
            mb.appendf("(%d) %s", xerrno, strerror(xerrno));
        else
            mb.append("[No Error]", 10);
        break;

    case 'f':
        if (building_deny_info_url) break;
        /* FTP REQUEST LINE */
        if (ftp.request)
            p = ftp.request;
        else
            p = "nothing";
        break;

    case 'F':
        if (building_deny_info_url) break;
        /* FTP REPLY LINE */
        if (ftp.reply)
            p = ftp.reply;
        else
            p = "nothing";
        break;

    case 'g':
        if (building_deny_info_url) break;
        /* FTP SERVER RESPONSE */
        if (ftp.listing) {
            mb.append(ftp.listing->content(), ftp.listing->contentSize());
            do_quote = 0;
        } else if (ftp.server_msg) {
            wordlistCat(ftp.server_msg, &mb);
        }
        break;

    case 'h':
        mb.appendf("%s", getMyHostname());
        break;

    case 'H':
        if (request) {
            if (request->hier.host[0] != '\0') // if non-empty string.
                p = request->hier.host;
            else
                p = request->url.host();
        } else if (!building_deny_info_url)
            p = "[unknown host]";
        break;

    case 'i':
        mb.appendf("%s", src_addr.toStr(ntoabuf,MAX_IPSTRLEN));
        break;

    case 'I':
        if (request && request->hier.tcpServer != NULL)
            p = request->hier.tcpServer->remote.toStr(ntoabuf,MAX_IPSTRLEN);
        else if (!building_deny_info_url)
            p = "[unknown]";
        break;

    case 'l':
        if (building_deny_info_url) break;
        mb.append(error_stylesheet.content(), error_stylesheet.contentSize());
        do_quote = 0;
        break;

    case 'L':
        if (building_deny_info_url) break;
        if (Config.errHtmlText) {
            mb.appendf("%s", Config.errHtmlText);
            do_quote = 0;
        } else
            p = "[not available]";
        break;

    case 'm':
        if (building_deny_info_url) break;
#if USE_AUTH
        if (auth_user_request.getRaw())
            p = auth_user_request->denyMessage("[not available]");
        else
            p = "[not available]";
#else
        p = "-";
#endif
        break;

    case 'M':
        if (request) {
            const SBuf &m = request->method.image();
            mb.append(m.rawContent(), m.length());
        } else if (!building_deny_info_url)
            p = "[unknown method]";
        break;

    case 'O':
        if (!building_deny_info_url)
            do_quote = 0;
    case 'o':
        p = request ? request->extacl_message.termedBuf() : external_acl_message;
        if (!p && !building_deny_info_url)
            p = "[not available]";
        break;

    case 'p':
        if (request) {
            mb.appendf("%u", request->url.port());
        } else if (!building_deny_info_url) {
            p = "[unknown port]";
        }
        break;

    case 'P':
        if (request) {
            const SBuf &m = request->url.getScheme().image();
            mb.append(m.rawContent(), m.length());
        } else if (!building_deny_info_url) {
            p = "[unknown protocol]";
        }
        break;

    case 'R':
        if (building_deny_info_url) {
            if (request != NULL) {
                SBuf tmp = request->url.path();
                p = tmp.c_str();
                no_urlescape = 1;
            } else
                p = "[no request]";
            break;
        }
        if (request != NULL) {
            mb.appendf(SQUIDSBUFPH " " SQUIDSBUFPH " %s/%d.%d\n",
                       SQUIDSBUFPRINT(request->method.image()),
                       SQUIDSBUFPRINT(request->url.path()),
                       AnyP::ProtocolType_str[request->http_ver.protocol],
                       request->http_ver.major, request->http_ver.minor);
            request->header.packInto(&mb, true); //hide authorization data
        } else if (request_hdrs) {
            p = request_hdrs;
        } else {
            p = "[no request]";
        }
        break;

    case 's':
        /* for backward compat we make %s show the full URL. Drop this in some future release. */
        if (building_deny_info_url) {
            if (request) {
                const SBuf &tmp = request->effectiveRequestUri();
                mb.append(tmp.rawContent(), tmp.length());
            } else
                p = url;
            debugs(0, DBG_CRITICAL, "WARNING: deny_info now accepts coded tags. Use %u to get the full URL instead of %s");
        } else
            p = visible_appname_string;
        break;

    case 'S':
        if (building_deny_info_url) {
            p = visible_appname_string;
            break;
        }
        /* signature may contain %-escapes, recursion */
        if (page_id != ERR_SQUID_SIGNATURE) {
            const int saved_id = page_id;
            page_id = ERR_SQUID_SIGNATURE;
            MemBuf *sign_mb = BuildContent();
            mb.append(sign_mb->content(), sign_mb->contentSize());
            sign_mb->clean();
            delete sign_mb;
            page_id = saved_id;
            do_quote = 0;
        } else {
            /* wow, somebody put %S into ERR_SIGNATURE, stop recursion */
            p = "[%S]";
        }
        break;

    case 't':
        mb.appendf("%s", Time::FormatHttpd(squid_curtime));
        break;

    case 'T':
        mb.appendf("%s", mkrfc1123(squid_curtime));
        break;

    case 'U':
        /* Using the fake-https version of absolute-URI so error pages see https:// */
        /* even when the url-path cannot be shown as more than '*' */
        if (request)
            p = urlCanonicalFakeHttps(request);
        else if (url)
            p = url;
        else if (!building_deny_info_url)
            p = "[no URL]";
        break;

    case 'u':
        if (request) {
            const SBuf &tmp = request->effectiveRequestUri();
            mb.append(tmp.rawContent(), tmp.length());
        } else if (url)
            p = url;
        else if (!building_deny_info_url)
            p = "[no URL]";
        break;

    case 'w':
        if (Config.adminEmail)
            mb.appendf("%s", Config.adminEmail);
        else if (!building_deny_info_url)
            p = "[unknown]";
        break;

    case 'W':
        if (building_deny_info_url) break;
        if (Config.adminEmail && Config.onoff.emailErrData)
            Dump(&mb);
        no_urlescape = 1;
        break;

    case 'x':
#if USE_OPENSSL
        if (detail)
            mb.appendf("%s", detail->errorName());
        else
#endif
            if (!building_deny_info_url)
                p = "[Unknown Error Code]";
        break;

    case 'z':
        if (building_deny_info_url) break;
        if (dnsError.size() > 0)
            p = dnsError.termedBuf();
        else if (ftp.cwd_msg)
            p = ftp.cwd_msg;
        else
            p = "[unknown]";
        break;

    case 'Z':
        if (building_deny_info_url) break;
        if (err_msg)
            p = err_msg;
        else
            p = "[unknown]";
        break;

    case '%':
        p = "%";
        break;

    default:
        mb.appendf("%%%c", token);
        do_quote = 0;
        break;
    }

    if (!p)
        p = mb.buf;     /* do not use mb after this assignment! */

    assert(p);

    debugs(4, 3, "errorConvert: %%" << token << " --> '" << p << "'" );

    if (do_quote)
        p = html_quote(p);

    if (building_deny_info_url && !no_urlescape)
        p = rfc1738_escape_part(p);

    return p;
}