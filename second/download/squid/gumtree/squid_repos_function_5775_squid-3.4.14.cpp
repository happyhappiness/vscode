void
IpcIoFile::Notify(const int peerId)
{
    // TODO: Count and report the total number of notifications, pops, pushes.
    debugs(47, 7, HERE << "kid" << peerId);
    Ipc::TypedMsgHdr msg;
    msg.setType(Ipc::mtIpcIoNotification); // TODO: add proper message type?
    msg.putInt(KidIdentifier);
    const String addr = Ipc::Port::MakeAddr(Ipc::strandAddrPfx, peerId);
    Ipc::SendMessage(addr, msg);
}