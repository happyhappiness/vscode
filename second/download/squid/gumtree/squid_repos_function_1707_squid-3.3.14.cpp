static helper_stateful_request *
StatefulDequeue(statefulhelper * hlp)
{
    dlink_node *link;
    helper_stateful_request *r = NULL;

    if ((link = hlp->queue.head)) {
        r = (helper_stateful_request *)link->data;
        dlinkDelete(link, &hlp->queue);
        memFree(link, MEM_DLINK_NODE);
        -- hlp->stats.queue_size;
    }

    return r;
}