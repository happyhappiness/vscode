bool
HttpRequest::expectingBody(const HttpRequestMethod& unused, int64_t&) const
{
    fatal("Not implemented");
    return false;
}