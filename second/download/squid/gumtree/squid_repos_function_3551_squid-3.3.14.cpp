static int
connOkToAddRequest(ConnStateData * conn)
{
    int result = conn->getConcurrentRequestCount() < (Config.onoff.pipeline_prefetch ? 2 : 1);

    if (!result) {
        debugs(33, 3, HERE << conn->clientConnection << " max concurrent requests reached");
        debugs(33, 5, HERE << conn->clientConnection << " defering new request until one is done");
    }

    return result;
}