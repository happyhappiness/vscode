int
Ip::Qos::doTosLocalMiss(const Comm::ConnectionPointer &conn, const hier_code hierCode)
{
    tos_t tos = 0;
    if (Ip::Qos::TheConfig.tosSiblingHit && hierCode==SIBLING_HIT) {
        tos = Ip::Qos::TheConfig.tosSiblingHit;
        debugs(33, 2, "QOS: Sibling Peer hit with hier code=" << hierCode << ", TOS=" << int(tos));
    } else if (Ip::Qos::TheConfig.tosParentHit && hierCode==PARENT_HIT) {
        tos = Ip::Qos::TheConfig.tosParentHit;
        debugs(33, 2, "QOS: Parent Peer hit with hier code=" << hierCode << ", TOS=" << int(tos));
    } else if (Ip::Qos::TheConfig.preserveMissTos) {
        tos = fd_table[conn->fd].tosFromServer & Ip::Qos::TheConfig.preserveMissTosMask;
        tos = (tos & ~Ip::Qos::TheConfig.tosMissMask) | (Ip::Qos::TheConfig.tosMiss & Ip::Qos::TheConfig.tosMissMask);
        debugs(33, 2, "QOS: Preserving TOS on miss, TOS=" << int(tos));
    } else if (Ip::Qos::TheConfig.tosMiss) {
        tos = Ip::Qos::TheConfig.tosMiss & Ip::Qos::TheConfig.tosMissMask;
        debugs(33, 2, "QOS: Cache miss, setting TOS=" << int(tos));
    }
    return setSockTos(conn, tos);
}