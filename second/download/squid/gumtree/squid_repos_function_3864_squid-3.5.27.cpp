int
Ip::Qos::doTosLocalHit(const Comm::ConnectionPointer &conn)
{
    debugs(33, 2, "QOS: Setting TOS for local hit, TOS=" << int(Ip::Qos::TheConfig.tosLocalHit));
    return setSockTos(conn, Ip::Qos::TheConfig.tosLocalHit);
}