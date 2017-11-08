static const char *set_limit_req_body(cmd_parms *cmd, void *conf_,
                                      const char *arg)
{
    core_dir_config *conf = conf_;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);
    char *errp;

    if (err != NULL) {
        return err;
    }

    if (APR_SUCCESS != apr_strtoff(&conf->limit_req_body, arg, &errp, 10)) {
        return "LimitRequestBody argument is not parsable.";
    }
    if (*errp || conf->limit_req_body < 0) {
        return "LimitRequestBody requires a non-negative integer.";
    }

    return NULL;
}