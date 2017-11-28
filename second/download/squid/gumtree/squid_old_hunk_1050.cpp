        }
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
