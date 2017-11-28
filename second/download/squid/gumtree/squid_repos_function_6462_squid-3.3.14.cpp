void
Mgr::Request::pack(Ipc::TypedMsgHdr& msg) const
{
    msg.setType(Ipc::mtCacheMgrRequest);
    msg.putPod(requestorId);
    msg.putPod(requestId);
    params.pack(msg);

    msg.putFd(conn->fd);
}