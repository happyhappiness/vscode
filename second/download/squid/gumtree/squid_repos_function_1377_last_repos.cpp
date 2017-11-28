void
helper::submitRequest(Helper::Xaction *r)
{
    helper_server *srv;

    if ((srv = GetFirstAvailable(this)))
        helperDispatch(srv, r);
    else
        Enqueue(this, r);

    syncQueueStats();
}