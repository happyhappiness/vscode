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

