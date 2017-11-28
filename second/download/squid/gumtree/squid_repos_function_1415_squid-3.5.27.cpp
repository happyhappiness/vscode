void
SBufStatsAction::pack(Ipc::TypedMsgHdr& msg) const
{
    msg.setType(Ipc::mtCacheMgrResponse);
    msg.putPod(sbdata);
    msg.putPod(mbdata);
}