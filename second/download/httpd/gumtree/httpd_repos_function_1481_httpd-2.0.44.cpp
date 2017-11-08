static const char *set_max_streaming_buffer(cmd_parms *parms, void *dummy,
                                            const char *arg)
{
    apr_off_t val;
    char *err;
    val = (apr_off_t)strtol(arg, &err, 10);
    if (*err != 0) {
        return "MCacheMaxStreamingBuffer value must be a number";
    }
    sconf->max_streaming_buffer_size = val;
    return NULL;
}