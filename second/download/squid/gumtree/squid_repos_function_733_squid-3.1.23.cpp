bool
ClientHttpRequest::onlyIfCached()const
{
    assert(request);
    return request->cache_control &&
           EBIT_TEST(request->cache_control->mask, CC_ONLY_IF_CACHED);
}