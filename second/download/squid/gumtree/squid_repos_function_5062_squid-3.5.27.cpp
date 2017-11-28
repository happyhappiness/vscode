ConnStateData *
Http::NewServer(MasterXactionPointer &xact)
{
    return new Server(xact, false);
}