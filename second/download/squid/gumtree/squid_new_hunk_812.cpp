
    if (hlp->stats.queue_size > (int)hlp->childs.n_running * 2)
        fatalf("Too many queued %s requests", hlp->id_name);
}

static void
StatefulEnqueue(statefulhelper * hlp, Helper::Request * r)
{
    dlink_node *link = (dlink_node *)memAllocate(MEM_DLINK_NODE);
    dlinkAddTail(r, link, &hlp->queue);
    ++ hlp->stats.queue_size;

    /* do this first so idle=N has a chance to grow the child pool before it hits critical. */
