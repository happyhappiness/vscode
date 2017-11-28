const char *
Adaptation::Ecap::XactionRep::status() const
{
    static MemBuf buf;
    buf.reset();

    buf.append(" [", 2);

    if (makingVb)
        buf.Printf("M%d", static_cast<int>(makingVb));

    const BodyPipePointer &vp = theVirginRep.raw().body_pipe;
    if (!vp)
        buf.append(" !V", 3);
    else if (vp->stillConsuming(const_cast<XactionRep*>(this)))
        buf.append(" Vc", 3);
    else
        buf.append(" V?", 3);

    if (vbProductionFinished)
        buf.append(".", 1);


    buf.Printf(" A%d", static_cast<int>(proxyingAb));

    if (proxyingAb == opOn) {
        MessageRep *rep = dynamic_cast<MessageRep*>(theAnswerRep.get());
        Must(rep);
        const BodyPipePointer &ap = rep->raw().body_pipe;
        if (!ap)
            buf.append(" !A", 3);
        else if (ap->stillProducing(const_cast<XactionRep*>(this)))
            buf.append(" Ap", 3);
        else
            buf.append(" A?", 3);
    }

    buf.Printf(" %s%u]", id.Prefix, id.value);

    buf.terminate();

    return buf.content();
}