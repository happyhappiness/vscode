void
Comm::ConnOpener::start()
{
    Must(conn_ != NULL);

    /* outbound sockets have no need to be protocol agnostic. */
    if (!(Ip::EnableIpv6&IPV6_SPECIAL_V4MAPPING) && conn_->remote.IsIPv4()) {
        conn_->local.SetIPv4();
    }

    if (createFd())
        connect();
}