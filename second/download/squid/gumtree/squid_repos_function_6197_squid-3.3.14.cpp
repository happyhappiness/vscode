void
Ipc::Coordinator::handleSnmpRequest(const Snmp::Request& request)
{
    debugs(54, 4, HERE);

    Snmp::Response response(request.requestId);
    TypedMsgHdr message;
    response.pack(message);
    SendMessage(MakeAddr(strandAddrPfx, request.requestorId), message);

    AsyncJob::Start(new Snmp::Inquirer(request, strands_));
}