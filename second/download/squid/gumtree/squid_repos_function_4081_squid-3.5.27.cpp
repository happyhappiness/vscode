void
Adaptation::Ecap::XactionRep::useVirgin()
{
    debugs(93,3, HERE << status());
    Must(proxyingAb == opUndecided);
    proxyingAb = opNever;

    preserveVb("useVirgin");

    HttpMsg *clone = theVirginRep.raw().header->clone();
    // check that clone() copies the pipe so that we do not have to
    Must(!theVirginRep.raw().header->body_pipe == !clone->body_pipe);

    updateHistory(clone);
    sendAnswer(Answer::Forward(clone));
    Must(done());
}