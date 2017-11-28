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
