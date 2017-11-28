{
    static MemBuf buf;
    buf.reset();

    buf.append(" [", 2);

    if (proxyingVb == opOn) {
        const BodyPipePointer &vp = theVirginRep.raw().body_pipe;
        if (!canAccessVb)
            buf.append("x", 1);
        if (vp != NULL) { // XXX: but may not be stillConsuming()
            buf.append("Vb", 2);
        } else
            buf.append("V.", 2);
    }

    if (proxyingAb == opOn) {
        MessageRep *rep = dynamic_cast<MessageRep*>(theAnswerRep.get());
        Must(rep);
        const BodyPipePointer &ap = rep->raw().body_pipe;
        if (ap != NULL) { // XXX: but may not be stillProducing()
            buf.append(" Ab", 3);
        } else
            buf.append(" A.", 3);
    }

    buf.Printf(" ecapx%d]", id);

    buf.terminate();

    return buf.content();
}
