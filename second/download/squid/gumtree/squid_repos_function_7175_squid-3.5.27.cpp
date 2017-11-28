void
Mgr::Response::pack(Ipc::TypedMsgHdr& msg) const
{
    Must(requestId != 0);
    msg.setType(Ipc::mtCacheMgrResponse);
    msg.putPod(requestId);
    if (hasAction()) {
        msg.putString(action->name());
        action->pack(msg);
    }
}