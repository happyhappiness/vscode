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
