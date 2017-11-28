int
Ip::Qos::doNfmarkLocalHit(const Comm::ConnectionPointer &conn)
{
    debugs(33, 2, "QOS: Setting netfilter mark for local hit, mark=" << Ip::Qos::TheConfig.markLocalHit);
    return setSockNfmark(conn, Ip::Qos::TheConfig.markLocalHit);
}