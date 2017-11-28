void
helperStatefulReleaseServer(helper_stateful_server * srv)
{
    debugs(84, 3, HERE << "srv-" << srv->index << " flags.reserved = " << srv->flags.reserved);
    if (!srv->flags.reserved)
        return;

    ++ srv->stats.releases;

    srv->flags.reserved = false;
    if (srv->parent->OnEmptyQueue != NULL && srv->data)
        srv->parent->OnEmptyQueue(srv->data);

    helperStatefulServerDone(srv);
}