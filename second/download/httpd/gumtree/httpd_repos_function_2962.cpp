const char *ap_mpm_set_max_mem_free(cmd_parms *cmd, void *dummy,
                                    const char *arg)
{
    long value;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    value = strtol(arg, NULL, 0);
    if (value < 0 || errno == ERANGE)
        return apr_pstrcat(cmd->pool, "Invalid MaxMemFree value: ",
                           arg, NULL);

    ap_max_mem_free = (apr_uint32_t)value * 1024;

    return NULL;
}