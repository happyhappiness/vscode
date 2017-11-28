dlink_node *
dlinkNodeNew()
{
    if (dlink_node_pool == NULL)
        dlink_node_pool = memPoolCreate("Dlink list nodes", sizeof(dlink_node));

    /* where should we call delete dlink_node_pool;dlink_node_pool = NULL; */
    return (dlink_node *)dlink_node_pool->alloc();
}