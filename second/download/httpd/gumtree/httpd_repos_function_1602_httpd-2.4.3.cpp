static int check_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp,
                        server_rec *s)
{
    if (ap_exists_config_define("DUMP_CONFIG")) {
        apr_file_open_stdout(&out, ptemp);
        mod_info_module_cmds(NULL, NULL, ap_conftree, 0, 0);
    }

    return DECLINED;
}