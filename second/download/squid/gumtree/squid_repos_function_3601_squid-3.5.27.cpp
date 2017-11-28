void
ClientSocketContext::keepaliveNextRequest()
{
    ConnStateData * conn = http->getConn();

    debugs(33, 3, HERE << "ConnnStateData(" << conn->clientConnection << "), Context(" << clientConnection << ")");
    connIsFinished();
    conn->kick();
}