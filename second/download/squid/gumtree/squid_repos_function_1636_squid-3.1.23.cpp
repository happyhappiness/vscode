static void
StatefulEnqueue(statefulhelper * hlp, helper_stateful_request * r)
{
    dlink_node *link = (dlink_node *)memAllocate(MEM_DLINK_NODE);
    dlinkAddTail(r, link, &hlp->queue);
    hlp->stats.queue_size++;

    if (hlp->stats.queue_size < hlp->n_running)
        return;

    if (hlp->stats.queue_size > hlp->n_running * 2)
        fatalf("Too many queued %s requests", hlp->id_name);

    if (squid_curtime - hlp->last_queue_warn < 600)
        return;

    if (shutting_down || reconfiguring)
        return;

    hlp->last_queue_warn = squid_curtime;

    debugs(84, 0, "WARNING: All " << hlp->id_name << " processes are busy.");

    debugs(84, 0, "WARNING: " << hlp->stats.queue_size << " pending requests queued");
    debugs(84, 1, "Consider increasing the number of " << hlp->id_name << " processes in your config file.");

}