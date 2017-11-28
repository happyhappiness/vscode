void
helperStatefulSubmit(statefulhelper * hlp, const char *buf, HLPCB * callback, void *data, helper_stateful_server * lastserver)
{
    if (hlp == NULL) {
        debugs(84, 3, "helperStatefulSubmit: hlp == NULL");
        Helper::Reply nilReply;
        callback(data, nilReply);
        return;
    }

    Helper::Request *r = new Helper::Request(callback, data, buf);

    if ((buf != NULL) && lastserver) {
        debugs(84, 5, "StatefulSubmit with lastserver " << lastserver);
        assert(lastserver->flags.reserved);
        assert(!(lastserver->request));

        debugs(84, 5, "StatefulSubmit dispatching");
        helperStatefulDispatch(lastserver, r);
    } else {
        helper_stateful_server *srv;
        if ((srv = StatefulGetFirstAvailable(hlp))) {
            helperStatefulDispatch(srv, r);
        } else
            StatefulEnqueue(hlp, r);
    }

    debugs(84, DBG_DATA, "placeholder: '" << r->placeholder <<
           "', " << Raw("buf", buf, (!buf?0:strlen(buf))));
}