static void
helperStatefulKickQueue(statefulhelper * hlp)
{
    Helper::Xaction *r;
    helper_stateful_server *srv;

    while ((srv = StatefulGetFirstAvailable(hlp)) && (r = hlp->nextRequest()))
        helperStatefulDispatch(srv, r);
}