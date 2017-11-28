void
Ipc::TypedMsgHdr::address(const struct sockaddr_un& addr)
{
    allocName();
    name = addr;
    msg_name = &name;
    msg_namelen = SUN_LEN(&name);
}