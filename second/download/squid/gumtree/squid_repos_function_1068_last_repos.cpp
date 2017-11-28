void
SBufStatsAction::unpack(const Ipc::TypedMsgHdr& msg)
{
    msg.checkType(Ipc::mtCacheMgrResponse);
    msg.getPod(sbdata);
    msg.getPod(mbdata);
}