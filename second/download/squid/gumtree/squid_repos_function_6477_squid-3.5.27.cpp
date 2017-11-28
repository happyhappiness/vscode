void
Snmp::Session::unpack(const Ipc::TypedMsgHdr& msg)
{
    free();
    msg.getPod(Version);
    community_len = msg.getInt();
    if (community_len > 0) {
        community = static_cast<u_char*>(xmalloc(community_len + 1));
        Must(community != NULL);
        msg.getFixed(community, community_len);
        community[community_len] = 0;
    }
    msg.getPod(retries);
    msg.getPod(timeout);
    int len = msg.getInt();
    if (len > 0) {
        peername = static_cast<char*>(xmalloc(len + 1));
        Must(peername != NULL);
        msg.getFixed(peername, len);
        peername[len] = 0;
    }
    msg.getPod(remote_port);
    msg.getPod(local_port);
}