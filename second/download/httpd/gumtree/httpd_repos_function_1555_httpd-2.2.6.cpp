static const char *get_cfg_string(ef_dir_t *dc, ef_filter_t *filter, apr_pool_t *p)
{
    const char *debug_str = dc->debug == -1 ?
        "DebugLevel=0" : apr_psprintf(p, "DebugLevel=%d", dc->debug);
    const char *log_stderr_str = dc->log_stderr < 1 ?
        "NoLogStderr" : "LogStderr";
    const char *preserve_content_length_str = filter->preserves_content_length ?
        "PreservesContentLength" : "!PreserveContentLength";
    const char *intype_str = !filter->intype ?
        "*/*" : filter->intype;
    const char *outtype_str = !filter->outtype ?
        "(unchanged)" : filter->outtype;

    return apr_psprintf(p,
                        "ExtFilterOptions %s %s %s ExtFilterInType %s "
                        "ExtFilterOuttype %s",
                        debug_str, log_stderr_str, preserve_content_length_str,
                        intype_str, outtype_str);
}