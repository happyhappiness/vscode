ConnStateData *
Http::NewServer(MasterXactionPointer &xact)
{
    return new Http1::Server(xact, false);
}