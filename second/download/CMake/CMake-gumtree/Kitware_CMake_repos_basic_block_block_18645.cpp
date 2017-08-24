{
        size_t l_rtaDataSize = RTA_PAYLOAD(l_rta);
        switch(l_rta->rta_type)
        {
            case IFLA_ADDRESS:
            case IFLA_BROADCAST:
                l_addrSize += NLMSG_ALIGN(calcAddrLen(AF_PACKET, l_rtaDataSize));
                break;
            case IFLA_IFNAME:
                l_nameSize += NLMSG_ALIGN(l_rtaSize + 1);
                break;
            case IFLA_STATS:
                l_dataSize += NLMSG_ALIGN(l_rtaSize);
                break;
            default:
                break;
        }
    }