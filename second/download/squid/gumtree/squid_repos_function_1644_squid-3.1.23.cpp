static void
helperStatefulDispatch(helper_stateful_server * srv, helper_stateful_request * r)
{
    statefulhelper *hlp = srv->parent;

    if (!cbdataReferenceValid(r->data)) {
        debugs(84, 1, "helperStatefulDispatch: invalid callback data");
        helperStatefulRequestFree(r);
        helperStatefulReleaseServer(srv);
        return;
    }

    debugs(84, 9, "helperStatefulDispatch busying helper " << hlp->id_name << " #" << srv->index + 1);

    if (r->placeholder == 1) {
        /* a callback is needed before this request can _use_ a helper. */
        /* we don't care about releasing this helper. The request NEVER
         * gets to the helper. So we throw away the return code */
        r->callback(r->data, srv, NULL);
        /* throw away the placeholder */
        helperStatefulRequestFree(r);
        /* and push the queue. Note that the callback may have submitted a new
         * request to the helper which is why we test for the request*/

        if (srv->request == NULL)
            helperStatefulServerDone(srv);

        return;
    }

    srv->flags.busy = 1;
    srv->flags.reserved = 1;
    srv->request = r;
    srv->dispatch_time = current_time;
    comm_write(srv->wfd,
               r->buf,
               strlen(r->buf),
               helperStatefulDispatchWriteDone,	/* Handler */
               hlp, NULL);				/* Handler-data, free func */
    debugs(84, 5, "helperStatefulDispatch: Request sent to " <<
           hlp->id_name << " #" << srv->index + 1 << ", " <<
           (int) strlen(r->buf) << " bytes");

    srv->stats.uses++;
    hlp->stats.requests++;
}