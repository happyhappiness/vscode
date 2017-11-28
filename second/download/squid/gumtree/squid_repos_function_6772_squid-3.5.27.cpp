void Ipc::StrandSearchResponse::pack(TypedMsgHdr &hdrMsg) const
{
    hdrMsg.setType(mtStrandSearchResponse);
    strand.pack(hdrMsg);
}