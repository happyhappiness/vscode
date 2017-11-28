void
DiskdAction::pack(Ipc::TypedMsgHdr& hdrMsg) const
{
    hdrMsg.setType(Ipc::mtCacheMgrResponse);
    hdrMsg.putPod(data);
}