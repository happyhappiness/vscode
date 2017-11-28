void
httpHdrContRangeDestroy(HttpHdrContRange * range)
{
    assert(range);
    memFree(range, MEM_HTTP_HDR_CONTENT_RANGE);
}