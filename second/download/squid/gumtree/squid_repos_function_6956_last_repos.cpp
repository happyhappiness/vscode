void Ipc::HereIamMessage::pack(TypedMsgHdr &hdrMsg) const
{
    hdrMsg.setType(mtRegistration);
    strand.pack(hdrMsg);
}