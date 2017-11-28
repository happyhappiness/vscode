void
httpRequestFree(void *data)
{
    ClientHttpRequest *http = (ClientHttpRequest *)data;
    assert(http != NULL);
    delete http;
}