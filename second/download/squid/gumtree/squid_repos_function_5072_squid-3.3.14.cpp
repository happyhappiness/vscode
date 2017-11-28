void
Comm::ConnOpener::timeout(const CommTimeoutCbParams &)
{
    debugs(5, 5, HERE << conn_ << ": * - ERR took too long to receive response.");
    calls_.timeout_ = NULL;
    sendAnswer(COMM_TIMEOUT, ETIMEDOUT, "Comm::ConnOpener::timeout");
}