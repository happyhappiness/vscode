void
Snmp::Request::pack(Ipc::TypedMsgHdr& msg) const
{
    msg.setType(Ipc::mtSnmpRequest);
    msg.putPod(requestorId);
    msg.putPod(requestId);
    pdu.pack(msg);
    session.pack(msg);
    msg.putPod(address);

    // Requests sent to Coordinator have FDs. Requests sent to strands do not.
    if (fd >= 0)
        msg.putFd(fd);
}