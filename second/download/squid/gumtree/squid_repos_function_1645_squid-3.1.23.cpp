static void
helperKickQueue(helper * hlp)
{
    helper_request *r;
    helper_server *srv;

    while ((srv = GetFirstAvailable(hlp)) && (r = Dequeue(hlp)))
        helperDispatch(srv, r);
}