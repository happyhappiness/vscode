        if (!p)
#endif
            p = "-";
        break;

    case 'b':
        mb.Printf("%d", getMyPort());
        break;

    case 'B':
        if (building_deny_info_url) break;
        p = request ? Ftp::UrlWith2f(request) : "[no URL]";
        break;

    case 'c':
        if (building_deny_info_url) break;
        p = errorPageName(type);
        break;
