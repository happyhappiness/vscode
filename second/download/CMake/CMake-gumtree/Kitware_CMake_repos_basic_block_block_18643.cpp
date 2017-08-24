{
    struct ifaddrs *l_entry;

    char *l_index;
    char *l_name;
    char *l_addr;
    char *l_data;

    struct ifinfomsg *l_info = (struct ifinfomsg *)NLMSG_DATA(p_hdr);

    size_t l_nameSize = 0;
    size_t l_addrSize = 0;
    size_t l_dataSize = 0;

    size_t l_rtaSize = NLMSG_PAYLOAD(p_hdr, sizeof(struct ifinfomsg));
    struct rtattr *l_rta;
    for(l_rta = IFLA_RTA(l_info); RTA_OK(l_rta, l_rtaSize); l_rta = RTA_NEXT(l_rta, l_rtaSize))
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

    l_entry = uv__malloc(sizeof(struct ifaddrs) + sizeof(int) + l_nameSize + l_addrSize + l_dataSize);
    if (l_entry == NULL)
    {
        return -1;
    }
    memset(l_entry, 0, sizeof(struct ifaddrs));
    l_entry->ifa_name = "";

    l_index = ((char *)l_entry) + sizeof(struct ifaddrs);
    l_name = l_index + sizeof(int);
    l_addr = l_name + l_nameSize;
    l_data = l_addr + l_addrSize;

    /* Save the interface index so we can look it up when handling the
     * addresses.
     */
    memcpy(l_index, &l_info->ifi_index, sizeof(int));

    l_entry->ifa_flags = l_info->ifi_flags;

    l_rtaSize = NLMSG_PAYLOAD(p_hdr, sizeof(struct ifinfomsg));
    for(l_rta = IFLA_RTA(l_info); RTA_OK(l_rta, l_rtaSize); l_rta = RTA_NEXT(l_rta, l_rtaSize))
    {
        void *l_rtaData = RTA_DATA(l_rta);
        size_t l_rtaDataSize = RTA_PAYLOAD(l_rta);
        switch(l_rta->rta_type)
        {
            case IFLA_ADDRESS:
            case IFLA_BROADCAST:
            {
                size_t l_addrLen = calcAddrLen(AF_PACKET, l_rtaDataSize);
                makeSockaddr(AF_PACKET, (struct sockaddr *)l_addr, l_rtaData, l_rtaDataSize);
                ((struct sockaddr_ll *)l_addr)->sll_ifindex = l_info->ifi_index;
                ((struct sockaddr_ll *)l_addr)->sll_hatype = l_info->ifi_type;
                if(l_rta->rta_type == IFLA_ADDRESS)
                {
                    l_entry->ifa_addr = (struct sockaddr *)l_addr;
                }
                else
                {
                    l_entry->ifa_broadaddr = (struct sockaddr *)l_addr;
                }
                l_addr += NLMSG_ALIGN(l_addrLen);
                break;
            }
            case IFLA_IFNAME:
                strncpy(l_name, l_rtaData, l_rtaDataSize);
                l_name[l_rtaDataSize] = '\0';
                l_entry->ifa_name = l_name;
                break;
            case IFLA_STATS:
                memcpy(l_data, l_rtaData, l_rtaDataSize);
                l_entry->ifa_data = l_data;
                break;
            default:
                break;
        }
    }

    addToEnd(p_resultList, l_entry);
    return 0;
}