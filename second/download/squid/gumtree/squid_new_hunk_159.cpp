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
        mb.Printf("%s", getMyHostname());
        break;

    case 'H':
        if (request) {
            if (request->hier.host[0] != '\0') // if non-empty string.
                p = request->hier.host;
            else
                p = request->GetHost();
        } else if (!building_deny_info_url)
            p = "[unknown host]";
        break;

    case 'i':
        mb.Printf("%s", src_addr.NtoA(ntoabuf,MAX_IPSTRLEN));
        break;

    case 'I':
        if (request && request->hier.tcpServer != NULL)
            p = request->hier.tcpServer->remote.NtoA(ntoabuf,MAX_IPSTRLEN);
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
            mb.Printf("%s", Config.errHtmlText);
            do_quote = 0;
        } else
            p = "[not available]";
        break;

    case 'm':
        if (building_deny_info_url) break;
#if USE_AUTH
        p = auth_user_request->denyMessage("[not available]");
#else
        p = "-";
#endif
        break;

    case 'M':
        if (request)
            p = RequestMethodStr(request->method);
        else if (!building_deny_info_url)
            p= "[unknown method]";
        break;

    case 'o':
        p = request ? request->extacl_message.termedBuf() : external_acl_message;
        if (!p && !building_deny_info_url)
            p = "[not available]";
        break;

    case 'p':
        if (request) {
            mb.Printf("%d", (int) request->port);
        } else if (!building_deny_info_url) {
            p = "[unknown port]";
        }
        break;

    case 'P':
        if (request) {
            p = AnyP::ProtocolType_str[request->protocol];
        } else if (!building_deny_info_url) {
            p = "[unknown protocol]";
        }
        break;

    case 'R':
        if (building_deny_info_url) {
            p = (request->urlpath.size() != 0 ? request->urlpath.termedBuf() : "/");
            no_urlescape = 1;
            break;
        }
        if (NULL != request) {
            Packer pck;
            String urlpath_or_slash;

            if (request->urlpath.size() != 0)
                urlpath_or_slash = request->urlpath;
            else
                urlpath_or_slash = "/";

            mb.Printf("%s " SQUIDSTRINGPH " %s/%d.%d\n",
                      RequestMethodStr(request->method),
                      SQUIDSTRINGPRINT(urlpath_or_slash),
                      AnyP::ProtocolType_str[request->http_ver.protocol],
                      request->http_ver.major, request->http_ver.minor);
            packerToMemInit(&pck, &mb);
            request->header.packInto(&pck, true); //hide authorization data
            packerClean(&pck);
        } else if (request_hdrs) {
            p = request_hdrs;
