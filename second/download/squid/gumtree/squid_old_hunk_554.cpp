                p = request->GetHost();
        } else if (!building_deny_info_url)
            p = "[unknown host]";
        break;

    case 'i':
        mb.Printf("%s", src_addr.NtoA(ntoabuf,MAX_IPSTRLEN));
        break;

    case 'I':
        if (request && request->hier.tcpServer != NULL)
            p = request->hier.tcpServer->remote.NtoA(ntoabuf,MAX_IPSTRLEN);
        else if (!building_deny_info_url)
            p = "[unknown]";
        break;

    case 'l':
        if (building_deny_info_url) break;
