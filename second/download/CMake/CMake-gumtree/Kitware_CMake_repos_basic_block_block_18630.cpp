{
    NetlinkList *l_item = uv__malloc(sizeof(NetlinkList));
    if (l_item == NULL)
    {
        return NULL;
    }

    l_item->m_next = NULL;
    l_item->m_data = p_data;
    l_item->m_size = p_size;
    return l_item;
}