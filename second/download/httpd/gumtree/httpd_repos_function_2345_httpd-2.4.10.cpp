static const char *set_kept_body_size(cmd_parms *cmd, void *dconf,
                                      const char *arg)
{
    request_dir_conf *conf = dconf;
    char *end = NULL;

    if (APR_SUCCESS != apr_strtoff(&(conf->keep_body), arg, &end, 10)
            || conf->keep_body < 0 || *end) {
        return "KeptBodySize must be a valid size in bytes, or zero.";
    }
    conf->keep_body_set = 1;

    return NULL;
}