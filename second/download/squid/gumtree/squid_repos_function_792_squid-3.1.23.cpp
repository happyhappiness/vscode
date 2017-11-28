void
HttpReply::hdrCacheClean()
{
    content_type.clean();

    if (cache_control) {
        httpHdrCcDestroy(cache_control);
        cache_control = NULL;
    }

    if (surrogate_control) {
        httpHdrScDestroy(surrogate_control);
        surrogate_control = NULL;
    }

    if (content_range) {
        httpHdrContRangeDestroy(content_range);
        content_range = NULL;
    }
}