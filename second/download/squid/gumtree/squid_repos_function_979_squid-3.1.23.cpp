void
dlinkNodeDelete(dlink_node * m)
{
    if (m == NULL)
        return;

    dlink_node_pool->free(m);
}