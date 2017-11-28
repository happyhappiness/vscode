void
Adaptation::Ecap::XactionRep::swanSong()
{
    // clear body_pipes, if any
    // this code does not maintain proxying* and canAccessVb states; should it?

    if (theAnswerRep != NULL) {
        BodyPipe::Pointer body_pipe = answer().body_pipe;
        if (body_pipe != NULL) {
            Must(body_pipe->stillProducing(this));
            stopProducingFor(body_pipe, false);
        }
    }

    if (proxyingVb == opOn) {
        BodyPipe::Pointer body_pipe = theVirginRep.raw().body_pipe;
        if (body_pipe != NULL) {
            Must(body_pipe->stillConsuming(this));
            stopConsumingFrom(body_pipe);
        }
    }

    terminateMaster();

    const HttpRequest *request = dynamic_cast<const HttpRequest*>(theCauseRep ?
                                 theCauseRep->raw().header : theVirginRep.raw().header);
    Must(request);
    Adaptation::History::Pointer ah = request->adaptLogHistory();
    if (ah != NULL && adaptHistoryId >= 0)
        ah->recordXactFinish(adaptHistoryId);

    Adaptation::Initiate::swanSong();
}