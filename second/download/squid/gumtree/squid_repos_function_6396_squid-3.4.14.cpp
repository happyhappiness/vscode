void
Ipc::Inquirer::HandleRemoteAck(const Response& response)
{
    Must(response.requestId != 0);
    AsyncCall::Pointer call = DequeueRequest(response.requestId);
    if (call != NULL) {
        HandleAckDialer* dialer = dynamic_cast<HandleAckDialer*>(call->getDialer());
        Must(dialer);
        dialer->arg1 = response.clone();
        ScheduleCallHere(call);
    }
}