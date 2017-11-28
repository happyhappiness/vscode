    safe_free(shortname);
    safe_free(procname);
    helperStatefulKickQueue(hlp);
}

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

/// lastserver = "server last used as part of a reserved request sequence"
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

/**
 * DPW 2007-05-08
 *
 * helperStatefulReleaseServer tells the helper that whoever was
