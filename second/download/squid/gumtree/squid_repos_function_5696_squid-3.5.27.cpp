void
Comm::AcceptLimiter::removeDead(const Comm::TcpAcceptor::Pointer &afd)
{
    uint64_t abandonedClients = 0;
    for (unsigned int i = 0; i < deferred_.size() && afd->isLimited > 0; ++i) {
        if (deferred_[i] == afd) {
            -- deferred_[i]->isLimited;
            deferred_[i] = NULL; // fast. kick() will skip empty entries later.
            debugs(5, 5, afd->conn << " x" << afd->isLimited);
            ++abandonedClients;
        }
    }
    debugs(5,4, "Abandoned " << abandonedClients << " client TCP SYN by closing socket: " << afd->conn);
}