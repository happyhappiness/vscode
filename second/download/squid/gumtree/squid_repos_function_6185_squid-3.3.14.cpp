void Ipc::StrandCoord::pack(TypedMsgHdr &hdrMsg) const
{
    hdrMsg.putPod(kidId);
    hdrMsg.putPod(pid);
    hdrMsg.putString(tag);
}