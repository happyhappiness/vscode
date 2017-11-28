void Adaptation::Icap::ModXact::fillPendingStatus(MemBuf &buf) const
{
    Adaptation::Icap::Xaction::fillPendingStatus(buf);

    if (state.serviceWaiting)
        buf.append("U", 1);

    if (virgin.body_pipe != NULL)
        buf.append("R", 1);

    if (haveConnection() && !doneReading())
        buf.append("r", 1);

    if (!state.doneWriting() && state.writing != State::writingInit)
        buf.Printf("w(%d)", state.writing);

    if (preview.enabled()) {
        if (!preview.done())
            buf.Printf("P(%d)", (int) preview.debt());
    }

    if (virginBodySending.active())
        buf.append("B", 1);

    if (!state.doneParsing() && state.parsing != State::psIcapHeader)
        buf.Printf("p(%d)", state.parsing);

    if (!doneSending() && state.sending != State::sendingUndecided)
        buf.Printf("S(%d)", state.sending);

    if (state.readyForUob)
        buf.append("6", 1);

    if (canStartBypass)
        buf.append("Y", 1);

    if (protectGroupBypass)
        buf.append("G", 1);
}