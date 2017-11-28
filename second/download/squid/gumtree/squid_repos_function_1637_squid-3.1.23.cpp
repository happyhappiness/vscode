static helper_request *
Dequeue(helper * hlp)
{
    dlink_node *link;
    helper_request *r = NULL;

    if ((link = hlp->queue.head)) {
        r = (helper_request *)link->data;
        dlinkDelete(link, &hlp->queue);
        memFree(link, MEM_DLINK_NODE);
        hlp->stats.queue_size--;
    }

    return r;
}