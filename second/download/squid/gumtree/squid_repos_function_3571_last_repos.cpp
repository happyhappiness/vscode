void Adaptation::Icap::ModXact::fillDoneStatus(MemBuf &buf) const
{
    Adaptation::Icap::Xaction::fillDoneStatus(buf);

    if (!virgin.body_pipe)
        buf.append("R", 1);

    if (state.doneWriting())
        buf.append("w", 1);

    if (preview.enabled()) {
        if (preview.done())
            buf.appendf("P%s", preview.ieof() ? "(ieof)" : "");
    }

    if (doneReading())
        buf.append("r", 1);

    if (state.doneParsing())
        buf.append("p", 1);

    if (doneSending())
        buf.append("S", 1);
}