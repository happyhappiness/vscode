void
ClientSocketContext::doneWithControlMsg()
{
    ScheduleCallHere(cbControlMsgSent);
    cbControlMsgSent = NULL;

    debugs(33, 3, clientConnection << ": calling PushDeferredIfNeeded after control msg wrote");
    ClientSocketContextPushDeferredIfNeeded(this, getConn());

}