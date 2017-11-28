static void
commConnectFree(int fd, void *data)
{
    ConnectStateData *cs = (ConnectStateData *)data;
    debugs(5, 3, "commConnectFree: FD " << fd);
//    delete cs->callback;
    cs->callback = NULL;
    safe_free(cs->host);
    delete cs;
}