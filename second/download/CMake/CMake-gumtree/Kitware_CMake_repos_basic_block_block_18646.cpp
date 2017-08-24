{
        char *l_indexPtr = ((char *)l_cur) + sizeof(struct ifaddrs);
        int l_index;
        memcpy(&l_index, l_indexPtr, sizeof(int));
        if(l_index == p_index)
        {
            return l_cur;
        }

        l_cur = l_cur->ifa_next;
        ++l_num;
    }