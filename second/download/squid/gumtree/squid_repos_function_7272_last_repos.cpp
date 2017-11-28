void
Mgr::StoreIoAction::pack(Ipc::TypedMsgHdr& msg) const
{
    msg.setType(Ipc::mtCacheMgrResponse);
    msg.putPod(data);
}