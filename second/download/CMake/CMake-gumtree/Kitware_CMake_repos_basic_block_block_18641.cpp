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