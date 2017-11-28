void
Ipc::Forwarder::HandleRemoteAck(unsigned int requestId)
{
    debugs(54, 3, HERE);
    Must(requestId != 0);

    AsyncCall::Pointer call = DequeueRequest(requestId);
    if (call != NULL)
        ScheduleCallHere(call);
}