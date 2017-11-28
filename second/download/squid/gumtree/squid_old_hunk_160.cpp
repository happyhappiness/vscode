            packerClean(&pck);
        } else if (request_hdrs) {
            p = request_hdrs;
        } else {
            p = "[no request]";
        }

        break;

    case 's':
        p = visible_appname_string;
        break;

    case 'S':
        /* signature may contain %-escapes, recursion */

        if (page_id != ERR_SQUID_SIGNATURE) {
            const int saved_id = page_id;
            page_id = ERR_SQUID_SIGNATURE;
            MemBuf *sign_mb = BuildContent();
            mb.Printf("%s", sign_mb->content());
            sign_mb->clean();
