static void
helperStatefulServerDone(helper_stateful_server * srv)
{
    if (!srv->flags.shutdown) {
        helperStatefulKickQueue(srv->parent);
    } else if (!srv->flags.closing && !srv->flags.reserved && !srv->flags.busy) {
        srv->closeWritePipeSafely();
        return;
    }
}