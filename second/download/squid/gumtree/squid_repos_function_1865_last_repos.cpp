void
GetMarkingsToServer(HttpRequest * request, Comm::Connection &conn)
{
    // Get the server side TOS and Netfilter mark to be set on the connection.
    if (Ip::Qos::TheConfig.isAclTosActive()) {
        conn.tos = GetTosToServer(request);
        debugs(17, 3, "from " << conn.local << " tos " << int(conn.tos));
    }

#if SO_MARK && USE_LIBCAP
    conn.nfmark = GetNfmarkToServer(request);
    debugs(17, 3, "from " << conn.local << " netfilter mark " << conn.nfmark);
#else
    conn.nfmark = 0;
#endif
}