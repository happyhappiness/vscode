static Helper::Request *
Dequeue(helper * hlp)
{
    dlink_node *link;
    Helper::Request *r = NULL;

    if ((link = hlp->queue.head)) {
        r = (Helper::Request *)link->data;
        dlinkDelete(link, &hlp->queue);
        memFree(link, MEM_DLINK_NODE);
        -- hlp->stats.queue_size;
    }

    return r;
}