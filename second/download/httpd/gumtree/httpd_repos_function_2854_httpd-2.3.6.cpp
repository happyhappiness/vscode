static const char *set_allow2f(cmd_parms *cmd, void *d_, int arg)
{
    core_dir_config *d = d_;

    d->allow_encoded_slashes = arg != 0;
    return NULL;
}