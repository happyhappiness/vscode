bool
ClientHttpRequest::gotEnough() const
{
    /** TODO: should be querying the stream. */
    int64_t contentLength =
        memObject()->getReply()->bodySize(request->method);
    assert(contentLength >= 0);

    if (out.offset < contentLength)
        return false;

    return true;
}