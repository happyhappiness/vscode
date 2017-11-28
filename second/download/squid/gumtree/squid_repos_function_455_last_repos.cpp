void
ClientHttpRequest::noteBodyProducerAborted(BodyPipe::Pointer)
{
    assert(!virginHeadSource);
    stopConsumingFrom(adaptedBodySource);

    debugs(85,3, HERE << "REQMOD body production failed");
    if (request_satisfaction_mode) { // too late to recover or serve an error
        request->detailError(ERR_ICAP_FAILURE, ERR_DETAIL_CLT_REQMOD_RESP_BODY);
        const Comm::ConnectionPointer c = getConn()->clientConnection;
        Must(Comm::IsConnOpen(c));
        c->close(); // drastic, but we may be writing a response already
    } else {
        handleAdaptationFailure(ERR_DETAIL_CLT_REQMOD_REQ_BODY);
    }
}