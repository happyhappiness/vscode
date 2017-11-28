void
helperSubmit(helper * hlp, const char *buf, HLPCB * callback, void *data)
{
    if (hlp == NULL) {
        debugs(84, 3, "helperSubmit: hlp == NULL");
        HelperReply nilReply;
        callback(data, nilReply);
        return;
    }

    helper_request *r = new helper_request;
    helper_server *srv;

    r->callback = callback;
    r->data = cbdataReference(data);
    r->buf = xstrdup(buf);

    if ((srv = GetFirstAvailable(hlp)))
        helperDispatch(srv, r);
    else
        Enqueue(hlp, r);

    debugs(84, DBG_DATA, Raw("buf", buf, strlen(buf)));
}