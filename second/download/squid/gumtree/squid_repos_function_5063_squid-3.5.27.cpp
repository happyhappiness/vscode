ConnStateData *
Https::NewServer(MasterXactionPointer &xact)
{
    return new Http::Server(xact, true);
}