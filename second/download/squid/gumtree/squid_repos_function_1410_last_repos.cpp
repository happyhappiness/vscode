static void
helperKickQueue(helper * hlp)
{
    Helper::Xaction *r;
    helper_server *srv;

    while ((srv = GetFirstAvailable(hlp)) && (r = hlp->nextRequest()))
        helperDispatch(srv, r);
}