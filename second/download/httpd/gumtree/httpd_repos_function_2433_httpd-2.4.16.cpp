static const char *deflate_set_inflate_ratio_burst(cmd_parms *cmd,
                                                   void *dirconf,
                                                   const char *arg)
{
    deflate_dirconf_t *dc = (deflate_dirconf_t*) dirconf;
    int i;

    i = atoi(arg);
    if (i <= 0)
        return "DeflateInflateRatioBurst must be positive";

    dc->ratio_burst = i;

    return NULL;
}