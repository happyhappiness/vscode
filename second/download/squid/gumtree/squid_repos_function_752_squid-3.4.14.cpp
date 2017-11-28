bool
ClientHttpRequest::onlyIfCached()const
{
    assert(request);
    return request->cache_control &&
           request->cache_control->onlyIfCached();
}