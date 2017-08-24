r(l_hdr = p_netlinkList->m_data; NLMSG_OK(l_hdr, l_nlsize); l_hdr = NLMSG_NEXT(l_hdr, l_nlsize))
        {
            if((pid_t)l_hdr->nlmsg_pid != l_pid || (int)l_hdr->nlmsg_seq != p_socket)
            {
                continue;
            }

            if(l_hdr->nlmsg_type == NLMSG_DONE)
            {
                break;
            }

            if(l_hdr->nlmsg_type == RTM_NEWADDR)
            {
                if (interpretAddr(l_hdr, p_resultList, p_numLinks) == -1)
                {
                    return -1;
                }
            }
        }