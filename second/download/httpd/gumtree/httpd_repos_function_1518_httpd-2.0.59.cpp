static const char *set_max_streaming_buffer(cmd_parms *parms, void *dummy,
                                            const char *arg)
{
#if 0
    char *err;
    if (apr_strtoff(&sconf->max_streaming_buffer_size, arg, &err, 10) || *err) {
        return "MCacheMaxStreamingBuffer value must be a number";
    }
#else
    sconf->max_streaming_buffer_size = apr_atoi64(arg);
#endif
    return NULL;
}