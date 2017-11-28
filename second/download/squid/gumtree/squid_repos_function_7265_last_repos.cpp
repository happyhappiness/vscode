void
Mgr::IntParam::unpackValue(const Ipc::TypedMsgHdr& msg)
{
    array.clear();
    int count = msg.getInt();
    Must(count >= 0);
    for ( ; count > 0; --count)
        array.push_back(msg.getInt());
}