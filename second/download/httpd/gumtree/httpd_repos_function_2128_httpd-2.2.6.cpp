static const char *set_use_canonical_name(cmd_parms *cmd, void *d_,
                                          const char *arg)
{
    core_dir_config *d = d_;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);

    if (err != NULL) {
        return err;
    }

    if (strcasecmp(arg, "on") == 0) {
        d->use_canonical_name = USE_CANONICAL_NAME_ON;
    }
    else if (strcasecmp(arg, "off") == 0) {
        d->use_canonical_name = USE_CANONICAL_NAME_OFF;
    }
    else if (strcasecmp(arg, "dns") == 0) {
        d->use_canonical_name = USE_CANONICAL_NAME_DNS;
    }
    else {
        return "parameter must be 'on', 'off', or 'dns'";
    }

    return NULL;
}