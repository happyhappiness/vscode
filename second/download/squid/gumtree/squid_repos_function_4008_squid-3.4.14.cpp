void
Adaptation::Ecap::XactionRep::blockVirgin()
{
    debugs(93,3, HERE << status());
    Must(proxyingAb == opUndecided);
    proxyingAb = opNever;

    sinkVb("blockVirgin");

    updateHistory(NULL);
    sendAnswer(Answer::Block(service().cfg().key));
    Must(done());
}