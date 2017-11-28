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
