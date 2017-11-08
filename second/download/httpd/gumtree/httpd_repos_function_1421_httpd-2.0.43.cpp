static const char *set_max_streaming_buffer(cmd_parms *parms, void *dummy,
                                            const char *arg)
{
    cache_server_conf *conf;
    apr_off_t val;
    char *err;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    val = (apr_off_t)strtol(arg, &err, 10);
    if (*err != 0) {
        return "CacheMaxStreamingBuffer value must be a number";
    }
    conf->max_streaming_buffer_size = val;
    return NULL;
}