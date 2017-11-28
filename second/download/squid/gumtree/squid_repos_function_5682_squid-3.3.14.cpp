void
IpcIoFile::HandleNotification(const Ipc::TypedMsgHdr &msg)
{
    const int from = msg.getInt();
    debugs(47, 7, HERE << "from " << from);
    queue->clearReaderSignal(from);
    if (IamDiskProcess())
        DiskerHandleRequests();
    else
        HandleResponses("after notification");
}