void
Ident::Timeout(int fd, void *data)
{
    IdentStateData *state = (IdentStateData *)data;
    debugs(30, 3, "identTimeout: FD " << fd << ", " << state->my_peer);

    comm_close(fd);
}