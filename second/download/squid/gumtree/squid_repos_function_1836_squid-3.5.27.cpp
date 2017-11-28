static void
helperKickQueue(helper * hlp)
{
    Helper::Request *r;
    helper_server *srv;

    while ((srv = GetFirstAvailable(hlp)) && (r = Dequeue(hlp)))
        helperDispatch(srv, r);
}