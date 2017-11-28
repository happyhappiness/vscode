void Ipc::StrandSearchRequest::pack(TypedMsgHdr &hdrMsg) const
{
    hdrMsg.setType(mtStrandSearchRequest);
    hdrMsg.putPod(requestorId);
    hdrMsg.putString(tag);
}