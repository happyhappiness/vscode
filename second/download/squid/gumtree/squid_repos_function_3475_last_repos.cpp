void
Adaptation::Ecap::XactionRep::useAdapted(const libecap::shared_ptr<libecap::Message> &m)
{
    debugs(93,3, HERE << status());
    Must(m);
    theAnswerRep = m;
    Must(proxyingAb == opUndecided);

    HttpMsg *msg = answer().header;
    updateSources(msg);
    if (!theAnswerRep->body()) { // final, bodyless answer
        proxyingAb = opNever;
        updateHistory(msg);
        sendAnswer(Answer::Forward(msg));
    } else { // got answer headers but need to handle body
        proxyingAb = opOn;
        Must(!msg->body_pipe); // only host can set body pipes
        MessageRep *rep = dynamic_cast<MessageRep*>(theAnswerRep.get());
        Must(rep);
        rep->tieBody(this); // sets us as a producer
        Must(msg->body_pipe != NULL); // check tieBody

        updateHistory(msg);
        sendAnswer(Answer::Forward(msg));

        debugs(93,4, HERE << "adapter will produce body" << status());
        theMaster->abMake(); // libecap will produce
    }
}