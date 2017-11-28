void
Mgr::StringParam::pack(Ipc::TypedMsgHdr& msg) const
{
    msg.putPod(type);
    msg.putString(str);
}