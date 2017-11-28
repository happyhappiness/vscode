static helper_server *
GetFirstAvailable(helper * hlp)
{
    dlink_node *n;
    helper_server *srv;
    helper_server *selected = NULL;

    if (hlp->n_running == 0)
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

    /* Check for overload */
    if (!selected)
        return NULL;

    if (selected->stats.pending >= (hlp->concurrency ? hlp->concurrency : 1))
        return NULL;

    return selected;
}