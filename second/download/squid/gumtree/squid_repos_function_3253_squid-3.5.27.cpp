void
CollapsedForwarding::HandleNotification(const Ipc::TypedMsgHdr &msg)
{
    const int from = msg.getInt();
    debugs(17, 7, "from " << from);
    assert(queue.get());
    queue->clearReaderSignal(from);
    HandleNewData("after notification");
}