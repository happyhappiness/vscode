void
Comm::TcpAcceptor::acceptNext()
{
    Must(IsConnOpen(conn));
    debugs(5, 2, HERE << "connection on " << conn);
    acceptOne();
}