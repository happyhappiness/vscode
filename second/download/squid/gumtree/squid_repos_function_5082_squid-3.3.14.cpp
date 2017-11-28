void
Comm::TcpAcceptor::doAccept(int fd, void *data)
{
    try {
        debugs(5, 2, HERE << "New connection on FD " << fd);

        Must(isOpen(fd));
        TcpAcceptor *afd = static_cast<TcpAcceptor*>(data);

        if (!okToAccept()) {
            AcceptLimiter::Instance().defer(afd);
        } else {
            afd->acceptNext();
        }
        SetSelect(fd, COMM_SELECT_READ, Comm::TcpAcceptor::doAccept, afd, 0);

    } catch (const std::exception &e) {
        fatalf("FATAL: error while accepting new client connection: %s\n", e.what());
    } catch (...) {
        fatal("FATAL: error while accepting new client connection: [unkown]\n");
    }
}