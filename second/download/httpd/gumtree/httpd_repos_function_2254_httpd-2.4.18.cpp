int h2_req_ignore_trailer(const char *name, size_t len)
{
    return (h2_req_ignore_header(name, len) 
            || ignore_header(H2_LIT_ARGS(IgnoredRequestTrailers), name, len));
}