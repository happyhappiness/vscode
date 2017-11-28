void
Comm::TcpAcceptor::handleClosure(const CommCloseCbParams &io)
{
    closer_ = NULL;
    conn = NULL;
    Must(done());
}