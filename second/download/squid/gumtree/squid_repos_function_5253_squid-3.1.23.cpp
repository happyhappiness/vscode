void
IcmpPinger::SendResult(pingerReplyData &preply, int len)
{
    debugs(42, 2, HERE << "return result to squid. len=" << len);

    if (send(socket_to_squid, &preply, len, 0) < 0) {
        debugs(42, 0, "pinger: FATAL error on send: " << xstrerror());
        Close();
        exit(1);
    }
}