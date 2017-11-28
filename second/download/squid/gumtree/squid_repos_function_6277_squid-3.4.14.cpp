void Ipc::Coordinator::handleRegistrationRequest(const HereIamMessage& msg)
{
    registerStrand(msg.strand);

    // send back an acknowledgement; TODO: remove as not needed?
    TypedMsgHdr message;
    msg.pack(message);
    SendMessage(MakeAddr(strandAddrPfx, msg.strand.kidId), message);
}