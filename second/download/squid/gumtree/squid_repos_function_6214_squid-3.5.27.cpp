void
DiskdAction::unpack(const Ipc::TypedMsgHdr& hdrMsg)
{
    hdrMsg.checkType(Ipc::mtCacheMgrResponse);
    hdrMsg.getPod(data);
}