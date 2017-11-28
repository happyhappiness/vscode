void
Comm::ConnOpener::start()
{
    Must(conn_ != NULL);

    /* outbound sockets have no need to be protocol agnostic. */
    if (!(Ip::EnableIpv6&IPV6_SPECIAL_V4MAPPING) && conn_->remote.isIPv4()) {
        conn_->local.setIPv4();
    }

    conn_->noteStart();
    if (createFd())
        doConnect();
}