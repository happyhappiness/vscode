static bool
AddOpenedHttpSocket(const Comm::ConnectionPointer &conn)
{
    bool found = false;
    for (int i = 0; i < NHttpSockets && !found; ++i) {
        if ((found = HttpSockets[i] < 0))
            HttpSockets[i] = conn->fd;
    }
    return found;
}