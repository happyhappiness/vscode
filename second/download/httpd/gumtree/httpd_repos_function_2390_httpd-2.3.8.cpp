static const char *noloris_trusted(cmd_parms *cmd, void *cfg, const char *val)
{
    const char* err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (!err) {
        apr_hash_set(trusted, val, APR_HASH_KEY_STRING, &noloris_module);
    }
    return err;
}