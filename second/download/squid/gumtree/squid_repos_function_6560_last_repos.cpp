void
IcmpPinger::SendResult(pingerReplyData &preply, int len)
{
    debugs(42, 2, HERE << "return result to squid. len=" << len);

    if (send(socket_to_squid, &preply, len, 0) < 0) {
        int xerrno = errno;
        debugs(42, DBG_CRITICAL, "pinger: FATAL error on send: " << xstrerr(xerrno));
        Close();
        exit(1);
    }
}