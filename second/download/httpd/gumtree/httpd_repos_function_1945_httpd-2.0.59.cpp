static const char *set_limit_req_body(cmd_parms *cmd, void *conf_,
                                      const char *arg)
{
    core_dir_config *conf = conf_;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);
    char *errp;

    if (err != NULL) {
        return err;
    }

    /* WTF: If strtoul is not portable, then write a replacement.
     *      Instead we have an idiotic define in httpd.h that prevents
     *      it from being used even when it is available. Sheesh.
     */
    conf->limit_req_body = (apr_off_t)strtol(arg, &errp, 10);
    if (*errp != '\0') {
        return "LimitRequestBody requires a non-negative integer.";
    }

    return NULL;
}