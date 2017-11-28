void Ipc::SharedListenRequest::pack(TypedMsgHdr &hdrMsg) const
{
    hdrMsg.setType(mtSharedListenRequest);
    hdrMsg.putPod(*this);
}