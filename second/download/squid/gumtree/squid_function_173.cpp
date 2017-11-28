const char *
ErrorState::Convert(char token, bool allowRecursion)
{
    static MemBuf mb;
    const char *p = NULL;	/* takes priority over mb if set */
    int do_quote = 1;
    char ntoabuf[MAX_IPSTRLEN];

    mb.reset();

    switch (token) {

    case 'a':

        if (request && request->auth_user_request)
            p = request->auth_user_request->username();

        if (!p)
            p = "-";

        break;

    case 'b':
        // NP: dynamic location of proxy-port not supported on 3.1
        // display the generic well-known port instead
        p = "3128";
        break;

    case 'B':
        p = request ? ftpUrlWith2f(request) : "[no URL]";

        break;

    case 'c':
        p = errorPageName(type);

        break;

    case 'D':
        if (!allowRecursion)
            p = "%D";  // if recursion is not allowed, do not convert
#if USE_SSL
        // currently only SSL error details implemented
        else if (detail) {
            const String &errDetail = detail->toString();
            if (errDetail.defined()) {
                MemBuf *detail_mb  = ConvertText(errDetail.termedBuf(), false);
                mb.append(detail_mb->content(), detail_mb->contentSize());
                delete detail_mb;
                do_quote = 0;
            }
        }
#endif
        if (!mb.contentSize())
            mb.Printf("[No Error Detail]");
        break;

    case 'e':
        mb.Printf("%d", xerrno);

        break;

    case 'E':

        if (xerrno)
            mb.Printf("(%d) %s", xerrno, strerror(xerrno));
        else
            mb.Printf("[No Error]");

        break;

    case 'f':
        /* FTP REQUEST LINE */
        if (ftp.request)
            p = ftp.request;
        else
            p = "nothing";

        break;

    case 'F':
        /* FTP REPLY LINE */
        if (ftp.reply)
            p = ftp.reply;
        else
            p = "nothing";

        break;

    case 'g':
        /* FTP SERVER MESSAGE */
        wordlistCat(ftp.server_msg, &mb);

        break;

    case 'h':
        mb.Printf("%s", getMyHostname());
        break;

    case 'H':
        if (request) {
            if (request->hier.host[0] != '\0') // if non-empty string.
                p = request->hier.host;
            else
                p = request->GetHost();
        } else
            p = "[unknown host]";

        break;

    case 'i':
        mb.Printf("%s", src_addr.NtoA(ntoabuf,MAX_IPSTRLEN));

        break;

    case 'I':
        if (request && request->hier.host[0] != '\0') // if non-empty string
            mb.Printf("%s", request->hier.host);
        else
            p = "[unknown]";

        break;

    case 'l':
        mb.append(error_stylesheet.content(), error_stylesheet.contentSize());
        do_quote = 0;
        break;

    case 'L':
        if (Config.errHtmlText) {
            mb.Printf("%s", Config.errHtmlText);
            do_quote = 0;
        } else
            p = "[not available]";

        break;

    case 'm':
        p = auth_user_request->denyMessage("[not available]");

        break;

    case 'M':
        p = request ? RequestMethodStr(request->method) : "[unknown method]";

        break;

    case 'o':
        p = request ? request->extacl_message.termedBuf() : external_acl_message;
        if (!p)
            p = "[not available]";
        break;

    case 'p':
        if (request) {
            mb.Printf("%d", (int) request->port);
        } else {
            p = "[unknown port]";
        }

        break;

    case 'P':
        p = request ? ProtocolStr[request->protocol] : "[unknown protocol]";
        break;

    case 'R':

        if (NULL != request) {
            Packer pck;
            String urlpath_or_slash;

            if (request->urlpath.size() != 0)
                urlpath_or_slash = request->urlpath;
            else
                urlpath_or_slash = "/";

            mb.Printf("%s " SQUIDSTRINGPH " HTTP/%d.%d\n",
                      RequestMethodStr(request->method),
                      SQUIDSTRINGPRINT(urlpath_or_slash),
                      request->http_ver.major, request->http_ver.minor);
            packerToMemInit(&pck, &mb);
            request->header.packInto(&pck, true); //hide authorization data
            packerClean(&pck);
        } else if (request_hdrs) {
            p = request_hdrs;
        } else {
            p = "[no request]";
        }

        break;

    case 's':
        p = visible_appname_string;
        break;

    case 'S':
        /* signature may contain %-escapes, recursion */

        if (page_id != ERR_SQUID_SIGNATURE) {
            const int saved_id = page_id;
            page_id = ERR_SQUID_SIGNATURE;
            MemBuf *sign_mb = BuildContent();
            mb.Printf("%s", sign_mb->content());
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
        mb.Printf("%s", mkhttpdlogtime(&squid_curtime));
        break;

    case 'T':
        mb.Printf("%s", mkrfc1123(squid_curtime));
        break;

    case 'U':
        /* Using the fake-https version of canonical so error pages see https:// */
        /* even when the url-path cannot be shown as more than '*' */
        p = request ? urlCanonicalFakeHttps(request) : url ? url : "[no URL]";
        break;

    case 'u':
        p = request ? urlCanonical(request) : url ? url : "[no URL]";
        break;

    case 'w':

        if (Config.adminEmail)
            mb.Printf("%s", Config.adminEmail);
        else
            p = "[unknown]";

        break;

    case 'W':
        if (Config.adminEmail && Config.onoff.emailErrData)
            Dump(&mb);

        break;

    case 'x':
        p = "[Not Available]"; // not supported by 3.1
        break;

    case 'z':
        if (dnsError.size() > 0)
            p = dnsError.termedBuf();
        else
            p = "[unknown]";

        break;

    case 'Z':
        if (err_msg)
            p = err_msg;
        else
            p = "[unknown]";

        break;

    case '%':
        p = "%";

        break;

    default:
        mb.Printf("%%%c", token);

        do_quote = 0;

        break;
    }

    if (!p)
        p = mb.buf;		/* do not use mb after this assignment! */

    assert(p);

    debugs(4, 3, "errorConvert: %%" << token << " --> '" << p << "'" );

    if (do_quote)
        p = html_quote(p);

    return p;
}