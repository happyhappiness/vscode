static void unixd_dump_config(apr_pool_t *p, server_rec *s)
{
    apr_file_t *out = NULL;
    apr_uid_t uid = ap_unixd_config.user_id;
    apr_gid_t gid = ap_unixd_config.group_id;
    char *no_root = "";
    if (!ap_exists_config_define("DUMP_RUN_CFG"))
        return;
    if (geteuid() != 0)
        no_root = " not_used";
    apr_file_open_stdout(&out, p);
    apr_file_printf(out, "User: name=\"%s\" id=%lu%s\n",
                    ap_unixd_config.user_name, (unsigned long)uid, no_root);
    apr_file_printf(out, "Group: name=\"%s\" id=%lu%s\n",
                    ap_unixd_config.group_name, (unsigned long)gid, no_root);
    if (ap_unixd_config.chroot_dir)
        apr_file_printf(out, "ChrootDir: \"%s\"%s\n",
                        ap_unixd_config.chroot_dir, no_root);
}