static void
helperStatefulKickQueue(statefulhelper * hlp)
{
    Helper::Request *r;
    helper_stateful_server *srv;

    while ((srv = StatefulGetFirstAvailable(hlp)) && (r = StatefulDequeue(hlp)))
        helperStatefulDispatch(srv, r);
}