void Ipc::SharedListenResponse::pack(TypedMsgHdr &hdrMsg) const
{
    hdrMsg.setType(mtSharedListenResponse);
    hdrMsg.putPod(*this);
    hdrMsg.putFd(fd);
}