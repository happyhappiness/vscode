int
httpCachable(const HttpRequestMethod& method)
{
    /* GET and HEAD are cachable. Others are not. */

    // TODO: replase to HttpRequestMethod::isCachable() ?
    if (method != METHOD_GET && method != METHOD_HEAD)
        return 0;

    /* else cachable */
    return 1;
}