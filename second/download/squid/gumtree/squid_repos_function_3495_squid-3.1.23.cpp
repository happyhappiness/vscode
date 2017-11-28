static void
clientLifetimeTimeout(int fd, void *data)
{
    ClientHttpRequest *http = (ClientHttpRequest *)data;
    debugs(33, 1, "WARNING: Closing client " << http->getConn()->peer << " connection due to lifetime timeout");
    debugs(33, 1, "\t" << http->uri);
    comm_close(fd);
}