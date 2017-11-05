static const char* 
unixd_set_chroot_dir(cmd_parms *cmd, void *dummy,
                    const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }
    if (!ap_is_directory(cmd->pool, arg)) {
        return "ChrootDir must be a valid directory";
    }

    ap_unixd_config.chroot_dir = arg;
    return NULL;
}