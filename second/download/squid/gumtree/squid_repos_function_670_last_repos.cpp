void
HttpControlMsgSink::doneWithControlMsg()
{
    if (cbControlMsgSent) {
        ScheduleCallHere(cbControlMsgSent);
        cbControlMsgSent = nullptr;
    }
}