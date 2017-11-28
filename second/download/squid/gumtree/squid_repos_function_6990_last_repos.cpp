void Ipc::TypedMsgHdr::sync()
{
    if (msg_name) { // we have a name
        msg_name = &name;
    } else {
        Must(!msg_namelen && !msg_name);
    }

    if (msg_iov) { // we have a data component
        Must(msg_iovlen == 1);
        msg_iov = ios;
        ios[0].iov_base = &data;
        Must(ios[0].iov_len == sizeof(data));
    } else {
        Must(!msg_iovlen && !msg_iov);
    }

    if (msg_control) { // we have a control component
        Must(msg_controllen > 0);
        msg_control = &ctrl;
    } else {
        Must(!msg_controllen && !msg_control);
    }
    offset = 0;
}