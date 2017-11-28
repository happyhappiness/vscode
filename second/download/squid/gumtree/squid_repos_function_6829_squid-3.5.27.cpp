int
Ipc::TypedMsgHdr::getInt() const
{
    int n = 0;
    getPod(n);
    return n;
}