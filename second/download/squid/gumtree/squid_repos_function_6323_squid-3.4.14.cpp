void
Ipc::TypedMsgHdr::allocData()
{
    Must(!msg_iovlen && !msg_iov);
    msg_iovlen = 1;
    msg_iov = ios;
    ios[0].iov_base = &data;
    ios[0].iov_len = sizeof(data);
    data.type_ = 0;
    data.size = 0;
}