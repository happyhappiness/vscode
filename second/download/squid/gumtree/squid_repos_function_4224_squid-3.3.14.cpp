void Adaptation::Icap::OptXact::handleCommRead(size_t)
{
    if (parseResponse()) {
        Must(icapReply != NULL);
        // We read everything if there is no response body. If there is a body,
        // we cannot parse it because we do not support any opt-body-types, so
        // we leave readAll false which forces connection closure.
        readAll = !icapReply->header.getByNameListMember("Encapsulated",
                  "opt-body", ',').size();
        debugs(93, 7, HERE << "readAll=" << readAll);
        icap_tio_finish = current_time;
        setOutcome(xoOpt);
        sendAnswer(Answer::Forward(icapReply));
        Must(done()); // there should be nothing else to do
        return;
    }

    scheduleRead();
}