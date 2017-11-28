void
Ipc::TypedMsgHdr::allocName()
{
    Must(!msg_name && !msg_namelen);
    msg_name = &name;
    msg_namelen = sizeof(name); // is that the right size?
}