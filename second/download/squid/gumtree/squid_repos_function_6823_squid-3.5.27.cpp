Ipc::TypedMsgHdr &Ipc::TypedMsgHdr::operator =(const TypedMsgHdr &tmh)
{
    if (this != &tmh) { // skip assignment to self
        memcpy(this, &tmh, sizeof(*this));
        sync();
    }
    return *this;
}