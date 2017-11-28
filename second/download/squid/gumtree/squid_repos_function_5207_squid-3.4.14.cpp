void
Comm::AcceptLimiter::defer(const Comm::TcpAcceptor::Pointer &afd)
{
    ++ (afd->isLimited);
    debugs(5, 5, afd->conn << " x" << afd->isLimited);
    deferred_.push_back(afd);
}