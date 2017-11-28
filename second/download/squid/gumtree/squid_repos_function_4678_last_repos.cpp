ConnStateData *
Https::NewServer(MasterXactionPointer &xact)
{
    return new Http1::Server(xact, true);
}