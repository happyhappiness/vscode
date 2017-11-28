void
Adaptation::Ecap::XactionRep::useVirgin()
{
    debugs(93,3, HERE << status());
    Must(proxyingAb == opUndecided);
    proxyingAb = opNever;

    BodyPipePointer &vbody_pipe = theVirginRep.raw().body_pipe;

    HttpMsg *clone = theVirginRep.raw().header->clone();
    // check that clone() copies the pipe so that we do not have to
    Must(!vbody_pipe == !clone->body_pipe);

    if (proxyingVb == opOn) {
        Must(vbody_pipe->stillConsuming(this));
        // if libecap consumed, we cannot shortcircuit
        Must(!vbody_pipe->consumedSize());
        stopConsumingFrom(vbody_pipe);
        canAccessVb = false;
        proxyingVb = opComplete;
    } else if (proxyingVb == opUndecided) {
        vbody_pipe = NULL; // it is not our pipe anymore
        proxyingVb = opNever;
    }

    sendAnswer(clone);
    Must(done());
}