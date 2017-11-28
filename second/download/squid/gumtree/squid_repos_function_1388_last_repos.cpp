void statefulhelper::submit(const char *buf, HLPCB * callback, void *data, helper_stateful_server * lastserver)
{
    Helper::Xaction *r = new Helper::Xaction(callback, data, buf);

    if ((buf != NULL) && lastserver) {
        debugs(84, 5, "StatefulSubmit with lastserver " << lastserver);
        assert(lastserver->flags.reserved);
        assert(!lastserver->requests.size());

        debugs(84, 5, "StatefulSubmit dispatching");
        helperStatefulDispatch(lastserver, r);
    } else {
        helper_stateful_server *srv;
        if ((srv = StatefulGetFirstAvailable(this))) {
            helperStatefulDispatch(srv, r);
        } else
            StatefulEnqueue(this, r);
    }

    debugs(84, DBG_DATA, "placeholder: '" << r->request.placeholder <<
           "', " << Raw("buf", buf, (!buf?0:strlen(buf))));

    syncQueueStats();
}