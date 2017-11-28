void
Ipc::StrandCoord::unpack(const TypedMsgHdr &hdrMsg)
{
    hdrMsg.getPod(kidId);
    hdrMsg.getPod(pid);
    hdrMsg.getString(tag);
}