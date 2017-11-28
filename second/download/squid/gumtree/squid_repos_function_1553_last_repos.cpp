time_t
peerConnectTimeout(const CachePeer *peer)
{
    return peer->connect_timeout_raw > 0 ?
           peer->connect_timeout_raw : Config.Timeout.peer_connect;
}