static const char *set_buffer_size(cmd_parms *cmd, void *dconf, const char *arg) {
    buffer_conf *conf = dconf;

    if (APR_SUCCESS != apr_strtoff(&(conf->size), arg, NULL, 10) || conf->size
            <= 0) {
        return "BufferSize must be a size in bytes, and greater than zero";
    }
    conf->size_set = 1;

    return NULL;
}