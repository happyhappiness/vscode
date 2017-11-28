static helper_server *
GetFirstAvailable(const helper * hlp)
{
    dlink_node *n;
    helper_server *srv;
    helper_server *selected = NULL;
    debugs(84, 5, "GetFirstAvailable: Running servers " << hlp->childs.n_running);

    if (hlp->childs.n_running == 0)
        return NULL;

    /* Find "least" loaded helper (approx) */
    for (n = hlp->servers.head; n != NULL; n = n->next) {
        srv = (helper_server *)n->data;

        if (selected && selected->stats.pending <= srv->stats.pending)
            continue;

        if (srv->flags.shutdown)
            continue;

        if (!srv->stats.pending)
            return srv;

        if (selected) {
            selected = srv;
            break;
        }

        selected = srv;
    }

    if (!selected) {
        debugs(84, 5, "GetFirstAvailable: None available.");
        return NULL;
    }

    if (selected->stats.pending >= (hlp->childs.concurrency ? hlp->childs.concurrency : 1)) {
        debugs(84, 3, "GetFirstAvailable: Least-loaded helper is fully loaded!");
        return NULL;
    }

    debugs(84, 5, "GetFirstAvailable: returning srv-" << selected->index);
    return selected;
}