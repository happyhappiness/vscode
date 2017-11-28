void Adaptation::Icap::OptXact::handleCommConnected()
{
    scheduleRead();

    MemBuf requestBuf;
    requestBuf.init();
    makeRequest(requestBuf);
    debugs(93, 9, HERE << "request " << status() << ":\n" <<
           (requestBuf.terminate(), requestBuf.content()));
    icap_tio_start = current_time;
    scheduleWrite(requestBuf);
}