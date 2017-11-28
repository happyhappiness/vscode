void
helperSubmit(helper * hlp, const char *buf, HLPCB * callback, void *data)
{
    if (hlp == NULL) {
        debugs(84, 3, "helperSubmit: hlp == NULL");
        Helper::Reply nilReply;
        callback(data, nilReply);
        return;
    }

    Helper::Request *r = new Helper::Request(callback, data, buf);
    helper_server *srv;

    if ((srv = GetFirstAvailable(hlp)))
        helperDispatch(srv, r);
    else
        Enqueue(hlp, r);

    debugs(84, DBG_DATA, Raw("buf", buf, strlen(buf)));
}