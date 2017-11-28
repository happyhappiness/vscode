void
ConnStateData::start()
{
    BodyProducer::start();
    HttpControlMsgSink::start();

    if (port->disable_pmtu_discovery != DISABLE_PMTU_OFF &&
            (transparent() || port->disable_pmtu_discovery == DISABLE_PMTU_ALWAYS)) {
#if defined(IP_MTU_DISCOVER) && defined(IP_PMTUDISC_DONT)
        int i = IP_PMTUDISC_DONT;
        if (setsockopt(clientConnection->fd, SOL_IP, IP_MTU_DISCOVER, &i, sizeof(i)) < 0) {
            int xerrno = errno;
            debugs(33, 2, "WARNING: Path MTU discovery disabling failed on " << clientConnection << " : " << xstrerr(xerrno));
        }
#else
        static bool reported = false;

        if (!reported) {
            debugs(33, DBG_IMPORTANT, "NOTICE: Path MTU discovery disabling is not supported on your platform.");
            reported = true;
        }
#endif
    }

    typedef CommCbMemFunT<ConnStateData, CommCloseCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(33, 5, Dialer, this, ConnStateData::connStateClosed);
    comm_add_close_handler(clientConnection->fd, call);

    needProxyProtocolHeader_ = port->flags.proxySurrogate;
    if (needProxyProtocolHeader_) {
        if (!proxyProtocolValidateClient()) // will close the connection on failure
            return;
    } else
        whenClientIpKnown();

}