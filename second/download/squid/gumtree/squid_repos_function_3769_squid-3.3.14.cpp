int
Ip::Qos::doNfmarkLocalMiss(const Comm::ConnectionPointer &conn, const hier_code hierCode)
{
    nfmark_t mark = 0;
    if (Ip::Qos::TheConfig.markSiblingHit && hierCode==SIBLING_HIT) {
        mark = Ip::Qos::TheConfig.markSiblingHit;
        debugs(33, 2, "QOS: Sibling Peer hit with hier code=" << hierCode << ", Mark=" << mark);
    } else if (Ip::Qos::TheConfig.markParentHit && hierCode==PARENT_HIT) {
        mark = Ip::Qos::TheConfig.markParentHit;
        debugs(33, 2, "QOS: Parent Peer hit with hier code=" << hierCode << ", Mark=" << mark);
    } else if (Ip::Qos::TheConfig.preserveMissMark) {
        mark = fd_table[conn->fd].nfmarkFromServer & Ip::Qos::TheConfig.preserveMissMarkMask;
        mark = (mark & ~Ip::Qos::TheConfig.markMissMask) | (Ip::Qos::TheConfig.markMiss & Ip::Qos::TheConfig.markMissMask);
        debugs(33, 2, "QOS: Preserving mark on miss, Mark=" << mark);
    } else if (Ip::Qos::TheConfig.markMiss) {
        mark = Ip::Qos::TheConfig.markMiss & Ip::Qos::TheConfig.markMissMask;
        debugs(33, 2, "QOS: Cache miss, setting Mark=" << mark);
    }
    return setSockNfmark(conn, mark);
}