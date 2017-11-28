void
Comm::TcpAcceptor::handleClosure(const CommCloseCbParams &)
{
    closer_ = NULL;
    conn = NULL;
    Must(done());
}