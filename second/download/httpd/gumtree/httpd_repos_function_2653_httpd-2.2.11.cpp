static const char *match_no_op(const apr_strmatch_pattern *this_pattern,
                               const char *s, apr_size_t slen)
{
    return s;
}