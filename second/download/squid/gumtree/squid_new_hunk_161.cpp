            page_id = saved_id;
            do_quote = 0;
        } else {
            /* wow, somebody put %S into ERR_SIGNATURE, stop recursion */
            p = "[%S]";
        }
        break;

    case 't':
        mb.Printf("%s", Time::FormatHttpd(squid_curtime));
        break;

    case 'T':
        mb.Printf("%s", mkrfc1123(squid_curtime));
        break;

    case 'U':
        /* Using the fake-https version of canonical so error pages see https:// */
        /* even when the url-path cannot be shown as more than '*' */
        if (request)
            p = urlCanonicalFakeHttps(request);
        else if (url)
            p = url;
        else if (!building_deny_info_url)
            p = "[no URL]";
        break;

    case 'u':
        if (request)
            p = urlCanonical(request);
        else if (url)
            p = url;
        else if (!building_deny_info_url)
            p = "[no URL]";
        break;

    case 'w':
        if (Config.adminEmail)
            mb.Printf("%s", Config.adminEmail);
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
#if USE_SSL
        if (detail)
            mb.Printf("%s", detail->errorName());
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
        mb.Printf("%%%c", token);
        do_quote = 0;
        break;
    }

    if (!p)
        p = mb.buf;		/* do not use mb after this assignment! */

