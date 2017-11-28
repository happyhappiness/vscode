int
Ipc::TypedMsgHdr::type() const
{
    Must(msg_iovlen == 1);
    return data.type_;
}