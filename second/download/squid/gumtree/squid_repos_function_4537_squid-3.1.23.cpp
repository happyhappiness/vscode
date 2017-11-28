bool
HttpReply::expectingBody(const HttpRequestMethod&, int64_t&) const
{
    fatal ("Not implemented");
    return false;
}