void Adaptation::Icap::ModXact::handleCommConnected()
{
    Must(state.writing == State::writingConnect);

    startReading(); // wait for early errors from the ICAP server

    MemBuf requestBuf;
    requestBuf.init();

    makeRequestHeaders(requestBuf);
    debugs(93, 9, HERE << "will write" << status() << ":\n" <<
           (requestBuf.terminate(), requestBuf.content()));

    // write headers
    state.writing = State::writingHeaders;
    icap_tio_start = current_time;
    scheduleWrite(requestBuf);
}