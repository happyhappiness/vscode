void
ConnStateData::requestTimeout(const CommTimeoutCbParams &io)
{
    /*
    * Just close the connection to not confuse browsers
    * using persistent connections. Some browsers open
    * a connection and then do not use it until much
    * later (presumeably because the request triggering
    * the open has already been completed on another
    * connection)
    */
    debugs(33, 3, "requestTimeout: FD " << io.fd << ": lifetime is expired.");
    io.conn->close();
}