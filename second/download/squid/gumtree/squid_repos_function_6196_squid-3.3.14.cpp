void
Ipc::Coordinator::notifySearcher(const Ipc::StrandSearchRequest &request,
                                 const StrandCoord& strand)
{
    debugs(54, 3, HERE << "tell kid" << request.requestorId << " that " <<
           request.tag << " is kid" << strand.kidId);
    const StrandSearchResponse response(strand);
    TypedMsgHdr message;
    response.pack(message);
    SendMessage(MakeAddr(strandAddrPfx, request.requestorId), message);
}