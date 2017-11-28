void
helperStatefulSubmit(statefulhelper * hlp, const char *buf, HLPSCB * callback, void *data, helper_stateful_server * lastserver)
{
    if (hlp == NULL) {
        debugs(84, 3, "helperStatefulSubmit: hlp == NULL");
        callback(data, 0, NULL);
        return;
    }

    helper_stateful_request *r = new helper_stateful_request;

    r->callback = callback;
    r->data = cbdataReference(data);

    if (buf != NULL) {
        r->buf = xstrdup(buf);
        r->placeholder = 0;
    } else {
        r->buf = NULL;
        r->placeholder = 1;
    }

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

    debugs(84, 9, "helperStatefulSubmit: placeholder: '" << r->placeholder << "', buf '" << buf << "'.");
}