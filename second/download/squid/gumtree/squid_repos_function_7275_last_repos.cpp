void
Mgr::StringParam::unpackValue(const Ipc::TypedMsgHdr& msg)
{
    msg.getString(str);
}