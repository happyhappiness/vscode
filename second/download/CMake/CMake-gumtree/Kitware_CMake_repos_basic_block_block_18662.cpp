{
        size_t l_rtaDataSize = RTA_PAYLOAD(l_rta);
        if(l_info->ifa_family == AF_PACKET)
        {
            continue;
        }

        switch(l_rta->rta_type)
        {
            case IFA_ADDRESS:
            case IFA_LOCAL:
                if((l_info->ifa_family == AF_INET || l_info->ifa_family == AF_INET6) && !l_addedNetmask)
                {
                    /* Make room for netmask */
                    l_addrSize += NLMSG_ALIGN(calcAddrLen(l_info->ifa_family, l_rtaDataSize));
                    l_addedNetmask = 1;
                }
            case IFA_BROADCAST:
                l_addrSize += NLMSG_ALIGN(calcAddrLen(l_info->ifa_family, l_rtaDataSize));
                break;
            case IFA_LABEL:
                l_nameSize += NLMSG_ALIGN(l_rtaSize + 1);
                break;
            default:
                break;
        }
    }