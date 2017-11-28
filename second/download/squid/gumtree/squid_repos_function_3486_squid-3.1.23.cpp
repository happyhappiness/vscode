static int
connOkToAddRequest(ConnStateData * conn)
{
    int result = conn->getConcurrentRequestCount() < (Config.onoff.pipeline_prefetch ? 2 : 1);

    if (!result) {
        debugs(33, 3, "connOkToAddRequest: FD " << conn->fd <<
               " max concurrent requests reached");
        debugs(33, 5, "connOkToAddRequest: FD " << conn->fd <<
               " defering new request until one is done");
    }

    return result;
}