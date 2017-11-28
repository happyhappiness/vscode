void
Mgr::Action::sendResponse(unsigned int requestId)
{
    Response response(requestId, this);
    Ipc::TypedMsgHdr message;
    response.pack(message);
    Ipc::SendMessage(Ipc::Port::CoordinatorAddr(), message);
}