void
Ssl::ServerBump::attachServerSession(const Security::SessionPointer &s)
{
    if (serverSession)
        return;

    serverSession = s;
}