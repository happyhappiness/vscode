{
        l_cur = p_list;
        p_list = p_list->m_next;
        uv__free(l_cur->m_data);
        uv__free(l_cur);
    }