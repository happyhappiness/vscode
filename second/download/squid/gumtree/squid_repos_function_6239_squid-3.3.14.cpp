void
Ipc::TypedMsgHdr::allocControl()
{
    Must(!msg_control && !msg_controllen);
    msg_control = &ctrl;
    msg_controllen = sizeof(ctrl);
}