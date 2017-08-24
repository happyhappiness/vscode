{
        NetlinkList *l_item;

        struct nlmsghdr *l_hdr = getNetlinkResponse(p_socket, &l_size, &l_done);
        /* Error */
        if(!l_hdr)
        {
            freeResultList(l_list);
            return NULL;
        }

        l_item = newListItem(l_hdr, l_size);
        if (!l_item)
        {
            freeResultList(l_list);
            return NULL;
        }
        if(!l_list)
        {
            l_list = l_item;
        }
        else
        {
            l_end->m_next = l_item;
        }
        l_end = l_item;
    }