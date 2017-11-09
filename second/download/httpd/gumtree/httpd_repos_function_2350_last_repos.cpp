int h2_res_ignore_trailer(const char *name, size_t len)
{
    return ignore_header(H2_LIT_ARGS(IgnoredResponseTrailers), name, len);
}