            const SBuf &m = request->method.image();
            mb.append(m.rawContent(), m.length());
        } else if (!building_deny_info_url)
            p = "[unknown method]";
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
            p = request->url.getScheme().c_str();
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

            mb.Printf(SQUIDSBUFPH " " SQUIDSTRINGPH " %s/%d.%d\n",
                      SQUIDSBUFPRINT(request->method.image()),
                      SQUIDSTRINGPRINT(urlpath_or_slash),
                      AnyP::ProtocolType_str[request->http_ver.protocol],
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
        /* for backward compat we make %s show the full URL. Drop this in some future release. */
        if (building_deny_info_url) {
            p = request ? urlCanonical(request) : url;
            debugs(0, DBG_CRITICAL, "WARNING: deny_info now accepts coded tags. Use %u to get the full URL instead of %s");
        } else
            p = visible_appname_string;
        break;

    case 'S':
