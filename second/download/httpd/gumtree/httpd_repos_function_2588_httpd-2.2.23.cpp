static const char *set_max_spare_threads(cmd_parms *cmd, void *dummy,
                                         const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    ap_max_spare_threads = atoi(arg);
    return NULL;
}