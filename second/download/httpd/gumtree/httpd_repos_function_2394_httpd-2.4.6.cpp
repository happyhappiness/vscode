static const char *deflate_set_buffer_size(cmd_parms *cmd, void *dummy,
                                           const char *arg)
{
    deflate_filter_config *c = ap_get_module_config(cmd->server->module_config,
                                                    &deflate_module);
    int n = atoi(arg);

    if (n <= 0) {
        return "DeflateBufferSize should be positive";
    }

    c->bufferSize = (apr_size_t)n;

    return NULL;
}