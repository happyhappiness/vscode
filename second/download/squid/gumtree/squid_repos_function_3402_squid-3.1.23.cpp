int
ClientSocketContext::fd() const
{
    assert (http);
    assert (http->getConn() != NULL);
    return http->getConn()->fd;
}