        no_urlescape = 1;
        break;

    case 'x':
#if USE_OPENSSL
        if (detail)
            mb.Printf("%s", detail->errorName());
        else
#endif
            if (!building_deny_info_url)
                p = "[Unknown Error Code]";
        break;

