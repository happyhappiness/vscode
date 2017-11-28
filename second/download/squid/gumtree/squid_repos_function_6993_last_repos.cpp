void
Ipc::TypedMsgHdr::checkType(int destType) const
{
    Must(type() == destType);
}