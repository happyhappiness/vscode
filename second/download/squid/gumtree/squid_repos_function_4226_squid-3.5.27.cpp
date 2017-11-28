void Adaptation::Icap::Xaction::handleCommTimedout()
{
    debugs(93, 2, HERE << typeName << " failed: timeout with " <<
           theService->cfg().methodStr() << " " <<
           theService->cfg().uri << status());
    reuseConnection = false;
    const bool whileConnecting = connector != NULL;
    if (whileConnecting) {
        assert(!haveConnection());
        theService->noteConnectionFailed("timedout");
    } else
        closeConnection(); // so that late Comm callbacks do not disturb bypass
    throw TexcHere(whileConnecting ?
                   "timed out while connecting to the ICAP service" :
                   "timed out while talking to the ICAP service");
}