ConnStateData *
Http::Stream::getConn() const
{
    assert(http && http->getConn());
    return http->getConn();
}