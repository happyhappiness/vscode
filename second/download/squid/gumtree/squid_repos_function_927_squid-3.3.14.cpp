static
void
commHalfClosedCheck(void *)
{
    debugs(5, 5, HERE << "checking " << *TheHalfClosed);

    typedef DescriptorSet::const_iterator DSCI;
    const DSCI end = TheHalfClosed->end();
    for (DSCI i = TheHalfClosed->begin(); i != end; ++i) {
        Comm::ConnectionPointer c = new Comm::Connection; // XXX: temporary. make HalfClosed a list of these.
        c->fd = *i;
        if (!fd_table[c->fd].halfClosedReader) { // not reading already
            AsyncCall::Pointer call = commCbCall(5,4, "commHalfClosedReader",
                                                 CommIoCbPtrFun(&commHalfClosedReader, NULL));
            comm_read(c, NULL, 0, call);
            fd_table[c->fd].halfClosedReader = call;
        } else
            c->fd = -1; // XXX: temporary. prevent c replacement erase closing listed FD
    }

    WillCheckHalfClosed = false; // as far as we know
    commPlanHalfClosedCheck(); // may need to check again
}