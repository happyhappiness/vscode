void
CollapsedForwarding::Notify(const int workerId)
{
    // TODO: Count and report the total number of notifications, pops, pushes.
    debugs(17, 7, "to kid" << workerId);
    Ipc::TypedMsgHdr msg;
    msg.setType(Ipc::mtCollapsedForwardingNotification);
    msg.putInt(KidIdentifier);
    const String addr = Ipc::Port::MakeAddr(Ipc::strandAddrLabel, workerId);
    Ipc::SendMessage(addr, msg);
}