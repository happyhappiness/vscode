void
Comm::ConnOpener::earlyAbort(const CommCloseCbParams &io)
{
    debugs(5, 3, HERE << io.conn);
    calls_.earlyAbort_ = NULL;
    // NP: is closing or shutdown better?
    sendAnswer(Comm::ERR_CLOSING, io.xerrno, "Comm::ConnOpener::earlyAbort");
}