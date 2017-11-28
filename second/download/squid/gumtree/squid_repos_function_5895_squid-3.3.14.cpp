void
Snmp::Response::pack(Ipc::TypedMsgHdr& msg) const
{
    msg.setType(Ipc::mtSnmpResponse);
    msg.putPod(requestId);
    pdu.pack(msg);
}