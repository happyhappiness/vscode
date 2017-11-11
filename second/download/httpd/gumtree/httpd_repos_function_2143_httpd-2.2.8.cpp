static const char *set_allow2f(cmd_parms *cmd, void *d_, int arg)
{
    core_dir_config *d = d_;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);

    if (err != NULL) {
        return err;
    }

    d->allow_encoded_slashes = arg != 0;
    return NULL;
}