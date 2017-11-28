static helper_stateful_server *
StatefulGetFirstAvailable(statefulhelper * hlp)
{
    dlink_node *n;
    helper_stateful_server *srv = NULL;
    debugs(84, 5, "StatefulGetFirstAvailable: Running servers " << hlp->childs.n_running);

    if (hlp->childs.n_running == 0)
        return NULL;

    for (n = hlp->servers.head; n != NULL; n = n->next) {
        srv = (helper_stateful_server *)n->data;

        if (srv->flags.busy)
            continue;

        if (srv->flags.reserved)
            continue;

        if (srv->flags.shutdown)
            continue;

        if ((hlp->IsAvailable != NULL) && (srv->data != NULL) && !(hlp->IsAvailable(srv->data)))
            continue;

        debugs(84, 5, "StatefulGetFirstAvailable: returning srv-" << srv->index);
        return srv;
    }

    debugs(84, 5, "StatefulGetFirstAvailable: None available.");
    return NULL;
}