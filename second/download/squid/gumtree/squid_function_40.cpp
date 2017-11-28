const char *Adaptation::Icap::ServiceRep::status() const
{
    static MemBuf buf;

    buf.reset();
    buf.append("[", 1);

    if (up())
        buf.append("up", 2);
    else {
        buf.append("down", 4);
        if (isSuspended)
            buf.append(",susp", 5);

        if (!theOptions)
            buf.append(",!opt", 5);
        else if (!theOptions->valid())
            buf.append(",!valid", 7);
        else if (!theOptions->fresh())
            buf.append(",stale", 6);
    }

    if (detached())
        buf.append(",detached", 9);

    if (theOptionsFetcher.set())
        buf.append(",fetch", 6);

    if (notifying)
        buf.append(",notif", 6);

    if (theSessionFailures > 0)
        buf.Printf(",fail%d", theSessionFailures);

    buf.append("]", 1);
    buf.terminate();

    return buf.content();
}