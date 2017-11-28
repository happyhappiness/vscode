void
FwdState::pconnPush(int fd, const peer *_peer, const HttpRequest *req, const char *domain, IpAddress &client_addr)
{
    if (_peer) {
        fwdPconnPool->push(fd, _peer->name, _peer->http_port, domain, client_addr);
    } else {
        /* small performance improvement, using NULL for domain instead of listing it twice */
        /* although this will leave a gap open for url-rewritten domains to share a link */
        fwdPconnPool->push(fd, req->GetHost(), req->port, NULL, client_addr);
    }
}