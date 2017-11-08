static const char *deflate_set_inflate_limit(cmd_parms *cmd, void *dirconf,
                                      const char *arg)
{
    deflate_dirconf_t *dc = (deflate_dirconf_t*) dirconf;
    char *errp;

    if (APR_SUCCESS != apr_strtoff(&dc->inflate_limit, arg, &errp, 10)) {
        return "DeflateInflateLimitRequestBody is not parsable.";
    }
    if (*errp || dc->inflate_limit < 0) {
        return "DeflateInflateLimitRequestBody requires a non-negative integer.";
    }

    return NULL;
}