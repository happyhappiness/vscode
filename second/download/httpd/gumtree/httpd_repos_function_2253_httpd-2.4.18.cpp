int h2_req_ignore_header(const char *name, size_t len)
{
    return ignore_header(H2_LIT_ARGS(IgnoredRequestHeaders), name, len);
}