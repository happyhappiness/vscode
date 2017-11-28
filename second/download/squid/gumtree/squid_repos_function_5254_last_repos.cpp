void
Ftp::Relay::serverState(const Ftp::ServerState newState)
{
    Ftp::ServerState &cltState = updateMaster().serverState;
    debugs(9, 3, "client state was " << cltState << " now: " << newState);
    cltState = newState;
}