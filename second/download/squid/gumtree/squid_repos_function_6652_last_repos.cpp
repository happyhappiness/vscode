void
Snmp::Session::pack(Ipc::TypedMsgHdr& msg) const
{
    msg.putPod(Version);
    msg.putInt(community_len);
    if (community_len > 0) {
        Must(community != NULL);
        msg.putFixed(community, community_len);
    }
    msg.putPod(retries);
    msg.putPod(timeout);
    int len = peername != NULL ? strlen(peername) : 0;
    msg.putInt(len);
    if (len > 0)
        msg.putFixed(peername, len);
    msg.putPod(remote_port);
    msg.putPod(local_port);
}