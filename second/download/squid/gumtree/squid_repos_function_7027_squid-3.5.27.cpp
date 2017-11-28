void Ipc::Strand::registerSelf()
{
    debugs(54, 6, HERE);
    Must(!isRegistered);

    HereIamMessage ann(StrandCoord(KidIdentifier, getpid()));
    TypedMsgHdr message;
    ann.pack(message);
    SendMessage(Port::CoordinatorAddr(), message);
    setTimeout(6, "Ipc::Strand::timeoutHandler"); // TODO: make 6 configurable?
}