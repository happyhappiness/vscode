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
