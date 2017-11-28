static void
helperStatefulKickQueue(statefulhelper * hlp)
{
    helper_stateful_request *r;
    helper_stateful_server *srv;

    while ((srv = StatefulGetFirstAvailable(hlp)) && (r = StatefulDequeue(hlp)))
        helperStatefulDispatch(srv, r);
}