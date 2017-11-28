const char *Adaptation::Ecap::ServiceRep::status() const
{
    // TODO: move generic stuff from eCAP and ICAP to Adaptation
    static MemBuf buf;

    buf.reset();
    buf.append("[", 1);

    if (up())
        buf.append("up", 2);
    else
        buf.append("down", 4);

    if (detached())
        buf.append(",detached", 9);

    buf.append("]", 1);
    buf.terminate();

    return buf.content();
}