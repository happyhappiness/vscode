void
Mgr::ActionParams::pack(Ipc::TypedMsgHdr &msg) const
{
    msg.putString(httpUri);
    auto foo = SBufToString(httpMethod.image());
    msg.putString(foo);
    msg.putPod(httpFlags);
    msg.putString(httpOrigin);

    msg.putString(actionName);
    msg.putString(userName);
    msg.putString(password);
    queryParams.pack(msg);
}