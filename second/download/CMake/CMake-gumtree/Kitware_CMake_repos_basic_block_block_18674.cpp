{
    int l_socket;
    int l_result;
    int l_numLinks;
    NetlinkList *l_linkResults;
    NetlinkList *l_addrResults;

    if(!ifap)
    {
        return -1;
    }
    *ifap = NULL;

    l_socket = netlink_socket();
    if(l_socket < 0)
    {
        return -1;
    }

    l_linkResults = getResultList(l_socket, RTM_GETLINK);
    if(!l_linkResults)
    {
        close(l_socket);
        return -1;
    }

    l_addrResults = getResultList(l_socket, RTM_GETADDR);
    if(!l_addrResults)
    {
        close(l_socket);
        freeResultList(l_linkResults);
        return -1;
    }

    l_result = 0;
    l_numLinks = interpretLinks(l_socket, l_linkResults, ifap);
    if(l_numLinks == -1 || interpretAddrs(l_socket, l_addrResults, ifap, l_numLinks) == -1)
    {
        l_result = -1;
    }

    freeResultList(l_linkResults);
    freeResultList(l_addrResults);
    close(l_socket);
    return l_result;
}