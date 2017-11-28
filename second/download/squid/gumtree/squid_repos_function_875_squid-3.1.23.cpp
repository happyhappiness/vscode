void
ConnectStateData::Connect(int fd, void *me)
{
    ConnectStateData *cs = (ConnectStateData *)me;
    assert (cs->fd == fd);
    cs->connect();
}