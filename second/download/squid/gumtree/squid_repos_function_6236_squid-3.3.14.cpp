void
Ipc::TypedMsgHdr::prepForReading()
{
    memset(this, 0, sizeof(*this));
    allocName();
    allocData();
    allocControl();
}