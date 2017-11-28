void
Ftp::Server::changeState(const ServerState newState, const char *reason)
{
    if (master->serverState == newState) {
        debugs(33, 3, "client state unchanged at " << master->serverState <<
               " because " << reason);
        master->serverState = newState;
    } else {
        debugs(33, 3, "client state was " << master->serverState <<
               ", now " << newState << " because " << reason);
        master->serverState = newState;
    }
}